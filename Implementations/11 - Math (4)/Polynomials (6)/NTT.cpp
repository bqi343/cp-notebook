/**
* Description: Use if you are working with non-negative integers
* Source: See FFT
* Verification: http://codeforces.com/contest/632/problem/E
    * Faster: https://oj.uz/submission/66171
*/

using namespace VecOp;

const int MOD = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

namespace NTT {
    int get(int s) {
        return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
    }
    
    vi ntt(vi& a) { 
        int n = sz(a), x = get(n); 
        vi res, RES(n), roots(n);
        roots[0] = 1, roots[1] = po(root,(MOD-1)/n);
        FOR(i,2,n) roots[i] = mul(roots[i-1],roots[1]);
        
        res = a;
        FOR(i,1,x+1) {
            int inc = n>>i;
            F0R(j,inc) for (int k = 0; k < n; k += inc) {
                int t = 2*k%n+j;
                RES[k+j] = ad(res[t],mul(roots[k],res[t+inc]));
            }
            swap(res,RES);
        }
        
        return res;
    }
    
    vi ntt_rev(vi& a) {
        vi res = ntt(a);
        ll in = inv(sz(a));
        F0R(i,sz(res)) MUL(res[i],in);
        reverse(res.begin() + 1, res.end());
        return res;
    }
    
    vi conv(vi a, vi b) {
        int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
        if (s <= 0) return {};
        if (s <= 200) return a*b;
        
        a.resize(n); a = ntt(a);
        b.resize(n); b = ntt(b);
        
        F0R(i,n) MUL(a[i],b[i]);
        
        a = ntt_rev(a);
        a.resize(s);
        return a;
    }
}
