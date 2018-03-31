/**
* Description: Use if you are working with non-negative integers
* Source: KACTL
* Verification: http://codeforces.com/contest/632/submission/33953285
*/

int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}

namespace NTT {
    const ll mod = (119 << 23) + 1, root = 3; // = 998244353
    // For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
    // (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.
        
    ll modpow(ll b, ll p) { return !p?1:modpow(b*b%mod,p/2)*(p&1?b:1)%mod; }
    
    ll inv (ll b) { return modpow(b,mod-2); }
    
    vl ntt(vl& a) { 
        int n = a.size(), x = get(n); 
        vl res, RES(n), roots(n);
        roots[0] = 1, roots[1] = modpow(root,(mod-1)/n);
        FOR(i,2,n) roots[i] = roots[i-1]*roots[1] % mod;
        
        res = a;
        FOR(i,1,x+1) {
            int inc = n>>i;
            F0R(j,inc) for (int k = 0; k < n; k += inc) {
                int t = 2*k%n+j;
                RES[k+j] = (res[t]+roots[k]*res[t+inc]) % mod;
            }
            swap(res,RES);
        }
        
        return res;
    }
    
    vl ntt_rev(vl& a) {
        vl res = ntt(a);
        ll in = inv(a.size());
        F0R(i,sz(res)) res[i] = res[i]*in % mod;
        reverse(res.begin() + 1, res.end());
        return res;
    }
    
    vl brute(vl& a, vl& b) {
        vl c(sz(a)+sz(b)-1);
        F0R(i,sz(a)) F0R(j,sz(b)) c[i+j] = (c[i+j]+a[i]*b[j])%mod;
        return c;
    }
    
    vl conv(vl a, vl b) {
        int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
        if (s <= 0) return {};
        if (s <= 200) return brute(a,b);
        
        a.resize(n); a = ntt(a);
        b.resize(n); b = ntt(b);
        
        F0R(i,n) a[i] = a[i]*b[i] % mod;
        a = ntt_rev(a);
        
        a.resize(s);
        return a;
    }
}

int main() {
    vl X = NTT::conv({1,2,3,4,5,6,7,8}, {1,2,3,4,5,6,7,8});
    for (auto a: X) cout << a << "\n";
}