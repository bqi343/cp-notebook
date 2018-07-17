/**
* Description: MOD is power of a prime
* Verification: https://dmoj.ca/problem/tle17c4p5
*/

template<int SZ> struct ComboPower {
    pl fac[SZ+1], ifac[SZ+1], mod;
    ll MOD = 1;
    
    void init(pl _mod) { // prime, power
        mod = _mod; F0R(i,mod.s) MOD *= mod.f;
        
        fac[0] = ifac[0] = {1,0};
        FOR(i,1,SZ+1) {
            fac[i] = fac[i-1];
            int I = i, z = 0;
            while (I % mod.f == 0) I /= mod.f, z++;
            fac[i].f = fac[i].f*I%MOD; fac[i].s += z;
            ifac[i] = {NT::inv(fac[i].f,MOD),fac[i].s};
        }
    }

    ll comb(ll a, ll b) {
        if (a < b || a < 0 || b < 0) return 0;
        ll tmp = (fac[a].f*ifac[b].f%MOD)*ifac[a-b].f % MOD;
        ll z = fac[a].s-fac[b].s-fac[a-b].s;
        if (z >= mod.s) return 0;
        F0R(i,z) tmp = tmp*mod.f % MOD;
        return tmp;
    }
};
