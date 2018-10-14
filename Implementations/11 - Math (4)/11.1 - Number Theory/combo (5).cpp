/**
* Description: extends Combo to all natural numbers
* Verification: https://dmoj.ca/problem/tle17c4p5
*/

using namespace modOp;
using namespace factor1;

template<int SZ> struct combo {
    int MOD, fac[SZ+1], ifac[SZ+1];
    vpl factors;
    vi cnt[SZ+1];
    
    int mul_mod(int a, int b) { return (ll)a*b%MOD; }
    
    void init(ll _MOD) {
        MOD = _MOD; factors = factor(MOD);
        cnt[0].resize(sz(factors));
        
        fac[0] = ifac[0] = 1;
        FOR(i,1,SZ+1) {
            cnt[i] = cnt[i-1];
            
            int I = i;
            F0R(j,sz(factors)) 
                while (I % factors[j].f == 0) 
                    I /= factors[j].f, cnt[i][j] ++;
                
            fac[i] = mul_mod(I,fac[i-1]), ifac[i] = inv(fac[i],MOD);
        }
    }
    
    ll comb(ll a, ll b) {
        if (a < b || b < 0) return 0;
        ll tmp = mul_mod(mul_mod(fac[a],ifac[b]),ifac[a-b]);
        F0R(i,sz(factors)) {
            int t = cnt[a][i]-cnt[a-b][i]-cnt[b][i];
            tmp = mul_mod(tmp,po(factors[i].f,t));
        }
        return tmp;
    }
};