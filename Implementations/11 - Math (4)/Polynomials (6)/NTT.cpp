/**
 * Description: Use if you are working with non-negative integers
 * Source: KACTL, https://cp-algorithms.com/algebra/fft.html
 * Verification: ? http://codeforces.com/contest/632/problem/E
 */

// dependency: Modular Int, Vector Operators

const int MOD = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

namespace NTT {
    int size(int s) { return s > 1 ? 32 - __builtin_clz(s - 1) : 0; }

    vmi roots;
    
    void ntt(vmi& a) {
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
    
    vmi conv(vmi a, vmi b) {
        int s = sz(a)+sz(b)-1, L = size(s), n = 1<<L;
        if (s <= 0) return {};
        if (s <= 200) return a*b;
        
        roots.resz(n); int r = exp(root,(MOD-1)/n);
        roots[0] = 1; FOR(i,1,n) roots[i] = roots[i-1]*r;
        
        a.resz(n), ntt(a); b.resz(n), ntt(b);
        F0R(i,n) a[i] *= b[i];
        
        reverse(beg(roots)+1,en(roots));
        ntt(a); int in = inv(n); trav(x,a) x *= in;
        
        a.resz(s); return a;
    } // ~0.22s when sz(a) = sz(b) = 1<<19
    
    vi conv(vi a, vi b) { return toVi(conv(toVmi(a),toVmi(b))); }
}

using namespace NTT;