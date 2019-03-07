/**
 * Description: multiply two polynomials
 * Source: KACTL, https://cp-algorithms.com/algebra/fft.html
 * Verification: 
    * SPOJ polymul, CSA manhattan, CF Perfect Encoding
    * http://codeforces.com/contest/632/problem/E
 */

// Dependency: Modular Int
using namespace vecOp;

namespace FFT {
    int size(int s) { return s > 1 ? 32 - __builtin_clz(s - 1) : 0; }

    template<class T> void fft(vector<T>& a, vector<T>& roots) {
        int n = sz(a);
        
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit; if (i < j) swap(a[i], a[j]);
        }
        
        for (int len = 2; len <= n; len <<= 1) 
            for (int i = 0; i < n; i += len) 
                F0R(j,len/2) {
                    auto u = a[i+j], v = a[i+j+len/2]*roots[n/len*j];
                    a[i+j] = u+v, a[i+j+len/2] = u-v;
                }
    }
    
    void genRoots(vmi& roots) {
        int n = sz(roots); mi r = exp(mi(root),(MOD-1)/n);
        roots[0] = 1; FOR(i,1,n) roots[i] = roots[i-1]*r;
    }
    void genRoots(vcd& roots) {
        int n = sz(roots); ld ang = 2*PI/n;
        F0R(i,n) roots[i] = cd(cos(ang*i),sin(ang*i)); // is there a way to do this more quickly?
    }
    
    template<class T> vector<T> conv(vector<T> a, vector<T> b) {
        int s = sz(a)+sz(b)-1, L = size(s), n = 1<<L;
        if (s <= 0) return {};
        if (s <= 200) return a*b;
        vector<T> roots(n); genRoots(roots);
        
        a.resz(n), fft(a,roots); b.resz(n), fft(b,roots);
        F0R(i,n) a[i] *= b[i];
        reverse(beg(roots)+1,en(roots)); fft(a,roots); 
        
        T in = T(1)/T(n); trav(x,a) x *= in;
        a.resz(s); return a;
    } 
    
    vl convl(const vl& a, const vl& b) { 
        vcd X = conv(vcd(all(a)),vcd(all(b)));
        vl x(sz(X)); F0R(i,sz(X)) x[i] = round(X[i].real());
        return x;
    } // ~0.55s when sz(a)=sz(b)=1<<19
    vl convMod(const vl& a, const vl& b, ll mod) { // http://codeforces.com/contest/960/submission/37085144
        int s = sz(a)+sz(b)-1, L = size(s), n = 1<<L;
        
        vcd v1(n), v2(n), r1(n), r2(n);
        F0R(i,sz(a)) v1[i] = cd(a[i] >> 15, a[i] & 32767);
        F0R(i,sz(b)) v2[i] = cd(b[i] >> 15, b[i] & 32767);
        
        vcd roots(n); genRoots(roots);
        fft(v1,roots), fft(v2,roots);
        F0R(i,n) {
            int j = (i ? (n - i) : i);
            cd ans1 = (v1[i] + conj(v1[j])) * cd(0.5, 0);
            cd ans2 = (v1[i] - conj(v1[j])) * cd(0, -0.5);
            cd ans3 = (v2[i] + conj(v2[j])) * cd(0.5, 0);
            cd ans4 = (v2[i] - conj(v2[j])) * cd(0, -0.5);
            r1[i] = (ans1 * ans3) + (ans1 * ans4) * cd(0, 1);
            r2[i] = (ans2 * ans3) + (ans2 * ans4) * cd(0, 1);
        }
        reverse(beg(roots)+1,en(roots));
        fft(r1,roots), fft(r2,roots); F0R(i,n) r1[i] /= n, r2[i] /= n;
        
        vl ret(n);
        F0R(i,n) {
            ll av = (ll)round(r1[i].real());
            ll bv = (ll)round(r1[i].imag()) + (ll)round(r2[i].real());
            ll cv = (ll)round(r2[i].imag());
            av %= mod, bv %= mod, cv %= mod;
            ret[i] = (av << 30) + (bv << 15) + cv;
            ret[i] = (ret[i]%mod+mod)%mod;
        }
        
        ret.resz(s); return ret;
    } // ~0.8s when sz(a)=sz(b)=1<<19
}

using namespace FFT;