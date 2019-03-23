/**
 * Description: extends Combo to all natural numbers
 * Source: Own
 * Verification: https://dmoj.ca/problem/tle17c4p5
 * Dependency: Modular Int
 */

using namespace basicFactor;

template<int SZ> struct Combo {
    int MOD; vpi factors;
    mi fac[SZ], ifac[SZ]; vi cnt[SZ];

    void init(int _MOD) {
        MOD = _MOD;
        factors = factor(MOD);
        // factors = {{MOD,1}};
        cnt[0] = vi(sz(factors));
        fac[0] = ifac[0] = mi(1,MOD);

        FOR(i,1,SZ+1) {
            cnt[i] = cnt[i-1];
            int I = i;
            F0R(j,sz(factors)) while (I % factors[j].f == 0)
                I /= factors[j].f, cnt[i][j] ++;
            fac[i] = fac[i-1]*I; ifac[i] = 1/fac[i];
        }
    }

    mi comb(int a, int b) {
        if (a < b || b < 0) return mi(0,MOD);
        auto tmp = fac[a]*ifac[b]*ifac[a-b];
        F0R(i,sz(factors)) {
            int t = cnt[a][i]-cnt[a-b][i]-cnt[b][i];
            tmp *= exp(mi(factors[i].f,MOD),t);
        }
        return tmp;
    }
};
