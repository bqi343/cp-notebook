/**
* Description: Use if you are working with non-negative integers
* Source: KACTL, https://cp-algorithms.com/algebra/fft.html
* Verification: http://codeforces.com/contest/632/problem/E
*/

using namespace modOp;

const int MOD = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

namespace NTT {
    int get(int s) { return s > 1 ? 32 - __builtin_clz(s - 1) : 0; }

	vi roots;
	
	void ntt(vi& a) {
	    int n = sz(a);
	
	    for (int i = 1, j = 0; i < n; i++) {
	        int bit = n >> 1;
	        for (; j & bit; bit >>= 1) j ^= bit;
	        j ^= bit; if (i < j) swap(a[i], a[j]);
	    }
        
	    for (int len = 2; len <= n; len <<= 1) 
	        for (int i = 0; i < n; i += len) 
	            F0R(j,len/2) {
	                int u = a[i+j], v = mul(a[i+j+len/2],roots[n/len*j]);
	                a[i+j] = ad(u,v), a[i+j+len/2] = sub(u,v);
	            }
	}
    
    vi brute(const vi& a, const vi& b) {
        vi c(sz(a)+sz(b)-1);
        F0R(i,sz(a)) F0R(j,sz(b)) AD(c[i+j],mul(a[i],b[j]));
        return c;
    }
    
    vi conv(vi a, vi b) {
        int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
        if (s <= 0) return {};
        if (s <= 200) return brute(a,b);
        
        roots.resz(n); int r = po(root,(MOD-1)/n);
        roots[0] = 1; FOR(i,1,n) roots[i] = mul(r,roots[i-1]);
        
        a.resz(n), ntt(a); b.resz(n), ntt(b);
        F0R(i,n) MUL(a[i],b[i]);
        
        reverse(beg(roots)+1,en(roots));
        ntt(a); int in = inv(n); trav(x,a) MUL(x,in); 
        
        a.resz(s); return a;
    } // ~0.22s when sz(a) = sz(b) = 1<<19
}

using namespace NTT;