/**
* Description: calculates combinations mod a large prime
* Verification: Combo General
*/

template<int SZ> struct Combo {
    int fac[SZ+1], ifac[SZ+1];
    
    ll mul(ll a, ll b) { return a*b%MOD; }
    ll po (ll b, ll p) { return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD; }
    ll inv (ll b) { return po(b,MOD-2); }

    Combo() {
        fac[0] = ifac[0] = 1;
    	FOR(i,1,SZ+1) 
    	    fac[i] = mul(i,fac[i-1]), ifac[i] = inv(fac[i]);
    }
    
    
    ll comb(ll a, ll b) {
        if (a < b || b < 0) return 0;
        return mul(mul(fac[a],ifac[b]),ifac[a-b]);
    }
};
