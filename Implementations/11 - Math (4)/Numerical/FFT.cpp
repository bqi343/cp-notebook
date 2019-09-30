/**
 * Description: multiply two polynomials
 * Source: KACTL, https://cp-algorithms.com/algebra/fft.html
 * Verification: 
    * SPOJ polymul, CSA manhattan, CF Perfect Encoding
    * http://codeforces.com/contest/632/problem/E
 * Dependency: Modular Int
 */

typedef complex<double> cd;

const int MOD = (119 << 23) + 1, root = 3; // = 998244353
// NTT: For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

using namespace vecOp;

namespace FFT {
    constexpr int size(int s) { return s > 1 ? 32-__builtin_clz(s-1) : 0; }
    template<class T> bool small(const vector<T>& a, const vector<T>& b) { 
        return (ll)sz(a)*sz(b) <= 500000; // for small vectors, multiply directly
    } 

    void genRoots(vmi& roots) { // primitive n-th roots of unity
        int n = sz(roots); mi r = pow(mi(root),(MOD-1)/n);
        roots[0] = 1; FOR(i,1,n) roots[i] = roots[i-1]*r;
    }
    void genRoots(vcd& roots) { // change cd to complex<double> instead?
        int n = sz(roots); double ang = 2*PI/n;
        F0R(i,n) roots[i] = cd(cos(ang*i),sin(ang*i)); // is there a way to do this more quickly?
    }
    template<class T> void fft(vector<T>& a, const vector<T>& roots, bool inv = 0) {
        int n = sz(a);
        for (int i = 1, j = 0; i < n; i++) { // sort by reverse bit representation
            int bit = n >> 1;
            for (; j&bit; bit >>= 1) j ^= bit;
            j ^= bit; if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) 
            for (int i = 0; i < n; i += len) 
                F0R(j,len/2) {
                    int ind = n/len*j; if (inv && ind) ind = n-ind;
                    auto u = a[i+j], v = a[i+j+len/2]*roots[ind];
                    a[i+j] = u+v, a[i+j+len/2] = u-v;
                }
        if (inv) { T i = T(1)/T(n); trav(x,a) x *= i; }
    }

    template<class T> vector<T> mult(vector<T> a, vector<T> b) {
        int s = sz(a)+sz(b)-1, n = 1<<size(s);
        vector<T> roots(n); genRoots(roots);
        a.rsz(n), fft(a,roots); 
        b.rsz(n), fft(b,roots);
        F0R(i,n) a[i] *= b[i];
        fft(a,roots,1); return a;
    }
    vcd smart(const vcd& a, const vcd& b) { return mult(a,b); }
    vl smart(const vl& a, const vl& b) {
        auto X = smart(vcd(all(a)),vcd(all(b)));
        vl x(sz(X)); F0R(i,sz(X)) x[i] = round(X[i].real());
        return x;
    }
    vmi smart(const vmi& a, const vmi& b) { return mult(a,b); }
    vmi smart2(const vmi& a, const vmi& b) { // arbitrary MOD, ensure precision by splitting in half
        const int BIT = 15; 
        int s = sz(a)+sz(b)-1, n = 1<<size(s);
        vcd roots(n); genRoots(roots);
        
        vcd ax(n), bx(n);
        F0R(i,sz(a)) {
            int A = (int)a[i];
            ax[i] = cd(A>>BIT, A&((1<<BIT)-1)); // v1(x)=a1(x)+i*a0(x)
        }
        F0R(i,sz(b)) {
            int B = (int)b[i];
            bx[i] = cd(B>>BIT, B&((1<<BIT)-1)); // v2(x)=b1(x)+i*b0(x)
        }
        fft(ax,roots), fft(bx,roots);
        
        vcd v1(n), v0(n);
        F0R(i,n) {
            int j = (i ? (n-i) : i);
            cd a1 = (ax[i]+conj(ax[j]))*cd(0.5, 0);  // all should be real
            cd a0 = (ax[i]-conj(ax[j]))*cd(0, -0.5); 
            cd b1 = (bx[i]+conj(bx[j]))*cd(0.5, 0);  
            cd b0 = (bx[i]-conj(bx[j]))*cd(0, -0.5);
            v1[i] = a1*(b1+b0*cd(0,1));
            v0[i] = a0*(b1+b0*cd(0,1));
        }
        fft(v1,roots,1), fft(v0,roots,1);
        
        vmi ret(n);
        F0R(i,n) {
            ll V2 = (ll)round(v1[i].real()); // a0*b0
            ll V1 = (ll)round(v1[i].imag())+(ll)round(v0[i].real()); // a0*b1+a1*b0
            ll V0 = (ll)round(v0[i].imag()); // a1*b1
            ret[i] = ((((((V2%MOD)<<BIT)+V1)%MOD)<<BIT)+V0)%MOD;
        }
        ret.rsz(s); return ret;
    } // ~0.8s when sz(a)=sz(b)=1<<19
    template<class T> vector<T> conv(const vector<T>& a, const vector<T>& b) {
        if (small(a,b)) return a*b;
        return smart(a,b);
    } 
}

using namespace FFT;