/**
* Source: Own
* MOD is a large prime
* see ComboExtended for mods in the form p^k
*/

template<int SZ> struct Combo {
    ll fac[SZ+1], ifac[SZ+1];
    
    Combo() {
        fac[0] = ifac[0] = 1;
    	FOR(i,1,SZ+1) {
    	    fac[i] = i*fac[i-1] % MOD;
    	    ifac[i] = inv(fac[i]);
    	}
    }
    
    ll po (ll b, ll p) {
        return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD;
    }
    
    ll inv (ll b) { return po(b,MOD-2); }
    
    ll comb(ll a, ll b) {
        if (a < b) return 0;
        ll tmp = fac[a]*ifac[b] % MOD;
        tmp = tmp*ifac[a-b] % MOD;
        return tmp;
    }
};

typedef pair<ll,ll> pll;
    
template<int SZ> struct ComboExtended {
    pll fac[SZ+1], ifac[SZ+1], mod;
    ll MOD = 1;
    
    void init(pll _mod) { // prime, power
        mod = _mod; F0R(i,mod.s) MOD *= mod.f;
        
        fac[0] = ifac[0] = {1,0};
        FOR(i,1,SZ+1) {
            fac[i] = fac[i-1];
            int I = i, z = 0;
            while (I % mod.f == 0) I /= mod.f, z++;
            fac[i].f = fac[i].f*I%MOD; fac[i].s += z;
            ifac[i] = {inv(fac[i].f,MOD),fac[i].s};
        }
    }
    
    ll inv(ll a, ll b) { // 0 < a < b, gcd(a,b) = 1
        a %= b;
        if (a <= 1) return a;
        ll i = inv(b%a,a);
        ll tmp = -((b/a)*i+((b%a)*i)/a) % b;
        while (tmp < 0) tmp += b;
        return tmp;
    }

    ll comb(ll a, ll b) {
        if (a < b) return 0;
        ll tmp = (fac[a].f*ifac[b].f%MOD)*ifac[a-b].f % MOD;
        ll z = fac[a].s-fac[b].s-fac[a-b].s;
        if (z >= mod.s) return 0;
        F0R(i,z) tmp = tmp*mod.f % MOD;
        return tmp;
    }
};