/**
* Description: extends Combo to all natural numbers
* Source: Own
* Verification: https://dmoj.ca/problem/tle17c4p5
*/

using namespace modOp;
using namespace factor1;

template<int SZ> struct combo {
    int MOD, fac[SZ+1], ifac[SZ+1];
    vpl factors;
    vi cnt[SZ+1];
    
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
                
            fac[i] = mul(I,fac[i-1],MOD), ifac[i] = invGeneral(fac[i],MOD);
        }
    }
    
    ll comb(ll a, ll b) {
        if (a < b || b < 0) return 0;
        ll tmp = mul(mul(fac[a],ifac[b],MOD),ifac[a-b],MOD);
        F0R(i,sz(factors)) {
            int t = cnt[a][i]-cnt[a-b][i]-cnt[b][i];
            tmp = mul(tmp,po(factors[i].f,t),MOD);
        }
        return tmp;
    }
};