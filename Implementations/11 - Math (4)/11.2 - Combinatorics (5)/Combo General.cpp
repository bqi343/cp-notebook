/**
* Description: extends Combo to all natural numbers
* Verification: https://dmoj.ca/problem/tle17c4p5
*/

template<int SZ> struct ComboGeneral {
    int MOD, fac[SZ+1], ifac[SZ+1];
    vpi factors;
    vi cnt[SZ+1];
    
    ll mul(ll a, ll b) { return a*b%MOD; }
    ll po (ll b, ll p) { return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD; }

    void init(ll _MOD) {
        MOD = _MOD;
        factors = NT::fac(MOD);
        cnt[0].resize(sz(factors));
        
        fac[0] = ifac[0] = 1;
        FOR(i,1,SZ+1) {
            cnt[i] = cnt[i-1];
            
            int I = i;
            F0R(j,sz(factors)) 
                while (I % factors[j].f == 0) 
                    I /= factors[j].f, cnt[i][j] ++;
                
            fac[i] = mul(I,fac[i-1]), ifac[i] = NT::inv(fac[i],MOD);
        }
    }
    
    ll comb(ll a, ll b) {
        if (a < b || b < 0) return 0;
        ll tmp = mul(mul(fac[a],ifac[b]),ifac[a-b]);
        F0R(i,sz(factors)) {
            int t = cnt[a][i]-cnt[a-b][i]-cnt[b][i];
            tmp = mul(tmp,po(factors[i].f,t));
        }
        return tmp;
    }
};