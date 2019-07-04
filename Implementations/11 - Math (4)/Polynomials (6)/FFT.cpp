/**
 * Description: multiply two polynomials
 * Source: KACTL, https://cp-algorithms.com/algebra/fft.html
 * Verification: 
    * SPOJ polymul, CSA manhattan, CF Perfect Encoding
    * http://codeforces.com/contest/632/problem/E
 * Dependency: Modular Int
 */

const int MOD = (119 << 23) + 1, root = 3; // = 998244353
// NTT: For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

using namespace vecOp;

namespace FFT {
    constexpr int size(int s) { return s > 1 ? 32-__builtin_clz(s-1) : 0; }
    // if vectors are small then multiply directly
    template<class T> bool small(const vector<T>& a, const vector<T>& b) { return (ll)sz(a)*sz(b) <= 500000; } 

    void genRoots(vmi& roots) { // primitive n-th roots of unity
        int n = sz(roots); mi r = exp(mi(root),(MOD-1)/n);
        roots[0] = 1; FOR(i,1,n) roots[i] = roots[i-1]*r;
    }
    void genRoots(vcd& roots) { // change cd to complex<double> instead?
        int n = sz(roots); ld ang = 2*PI/n;
        F0R(i,n) roots[i] = cd(cos(ang*i),sin(ang*i)); // is there a way to do this more quickly?
    }
    
    template<class T> void fft(vector<T>& a, vector<T>& roots) {
        int n = sz(a);
        for (int i = 1, j = 0; i < n; i++) { // sort by reverse bit representation
            int bit = n >> 1;
            for (; j&bit; bit >>= 1) j ^= bit;
            j ^= bit; if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) 
            for (int i = 0; i < n; i += len) 
                F0R(j,len/2) {
                    auto u = a[i+j], v = a[i+j+len/2]*roots[n/len*j];
                    a[i+j] = u+v, a[i+j+len/2] = u-v;
                }
    }

    template<class T> vector<T> conv(vector<T> a, vector<T> b) {
        if (small(a,b)) return a*b;
        int s = sz(a)+sz(b)-1, n = 1<<size(s);
        vector<T> roots(n); genRoots(roots);
        
        a.rsz(n), fft(a,roots); b.rsz(n), fft(b,roots);
        F0R(i,n) a[i] *= b[i];
        reverse(begin(roots)+1,end(roots)); fft(a,roots); // inverse FFT
        
        T in = T(1)/T(n); trav(x,a) x *= in;
        a.rsz(s); return a;
    } 
    vl conv(const vl& a, const vl& b) { 
        if (small(a,b)) return a*b;
        vcd X = conv(vcd(all(a)),vcd(all(b)));
        vl x(sz(X)); F0R(i,sz(X)) x[i] = round(X[i].real());
        return x;
    } // ~0.55s when sz(a)=sz(b)=1<<19
    vl conv(const vl& a, const vl& b, ll mod) { // http://codeforces.com/contest/960/submission/37085144
        if (small(a,b)) return a*b;
        int s = sz(a)+sz(b)-1, n = 1<<size(s);
        
        vcd v1(n), v2(n), r1(n), r2(n);
        F0R(i,sz(a)) v1[i] = cd(a[i]>>15, a[i]&32767); // v1(x)=a0(x)+i*a1(x)
        F0R(i,sz(b)) v2[i] = cd(b[i]>>15, b[i]&32767); // v2(x)=b0(x)+i*b1(x)
        
        vcd roots(n); genRoots(roots);
        fft(v1,roots), fft(v2,roots);
        F0R(i,n) {
            int j = (i ? (n-i) : i);
            cd ans1 = (v1[i]+conj(v1[j]))*cd(0.5, 0); // a0(x)
            cd ans2 = (v1[i]-conj(v1[j]))*cd(0, -0.5); // a1(x)
            cd ans3 = (v2[i]+conj(v2[j]))*cd(0.5, 0); // b0(x)
            cd ans4 = (v2[i]-conj(v2[j]))*cd(0, -0.5); // b1(x)
            r1[i] = (ans1*ans3)+(ans1*ans4)*cd(0, 1); // a0(x)*v2(x)
            r2[i] = (ans2*ans3)+(ans2*ans4)*cd(0, 1); // a1(x)*v2(x)
        }
        reverse(begin(roots)+1,end(roots));
        fft(r1,roots), fft(r2,roots); F0R(i,n) r1[i] /= n, r2[i] /= n;
        
        vl ret(n);
        F0R(i,n) {
            ll av = (ll)round(r1[i].real()); // a0*b0
            ll bv = (ll)round(r1[i].imag())+(ll)round(r2[i].real()); // a0*b1+a1*b0
            ll cv = (ll)round(r2[i].imag()); // a1*b1
            av %= mod, bv %= mod, cv %= mod;
            ret[i] = (av<<30)+(bv<<15)+cv;
            ret[i] = (ret[i]%mod+mod)%mod;
        }
        ret.rsz(s); return ret;
    } // ~0.8s when sz(a)=sz(b)=1<<19
}

using namespace FFT;