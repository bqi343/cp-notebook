/**
* Description: Use if you are working with non-negative integers
* Source: See FFT
* Verification: http://codeforces.com/contest/632/problem/E
    * Faster: https://oj.uz/submission/66171
*/

using namespace modOp;

const int MOD = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

namespace NTT {
    int get(int s) { return s > 1 ? 32 - __builtin_clz(s - 1) : 0; }
    
    void ntt(vi& a) { 
        int N = sz(a), j = 0;
        
        FOR(i,1,N) {
            int k;
            for (k = N >> 1; j >= k; k >>= 1) j -= k;
            j += k; if (i < j) swap(a[i],a[j]);
        }
        
        vl roots(N);
        roots[0] = 1, roots[1] = po(root,(MOD-1)/N);
        FOR(i,2,N) roots[i] = mul(roots[i-1],roots[1]);
        
        for (int i = 2; i <= N; i *= 2) {
            int i2 = i/2;
            for (j = 0; j < N; j += i) {
                for (int k = 0; k < i2; k++) {
                    auto z = mul(a[i2+j+k],roots[N/i*k]); 
                    a[i2+j+k] = sub(a[j+k],z); AD(a[j+k],z);
                }
            }
        }
    } 
    
    vi ntt_rev(vi& a) {
        ll in = inv(sz(a));
        ntt(a); trav(x,a) MUL(x,in);
        reverse(beg(a)+1, en(a));
    }
    
    vi brute(const vi& a, const vi& b) {
        vi c(sz(a)+sz(b)-1);
        F0R(i,sz(a)) F0R(j,sz(b)) AD(c[i+j],mul(a[i],b[j]));
        return c;
    }
    
    vi conv(vi a, vi b) { 
        // 0.1s for sz(a)=sz(b)=1<<18, 0.2s for slower version
        int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
        if (s <= 0) return {};
        if (s <= 200) return brute(a,b);
        a.resz(n), ntt(a); b.resz(n), ntt(b);
        F0R(i,n) MUL(a[i],b[i]);
        ntt_rev(a); a.resz(s); return a;
    }
}

using namespace NTT;