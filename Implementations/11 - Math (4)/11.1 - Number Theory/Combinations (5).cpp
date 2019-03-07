/**
 * Description: extends Combo to all natural numbers
 * Source: Own
 * Verification: ? https://dmoj.ca/problem/tle17c4p5
 */

// dependency: Modular Int
using namespace factor1;

template<int SZ> struct Combo {
    int MOD;
    vpmi fac[SZ+1], ifac[SZ+1];
    vpi factors;
    vi cnt[SZ+1];
    
    void init(int _MOD) {
        MOD = _MOD; factors = factor(MOD); // factors = {{MOD,1}}; suffices if prime
        cnt[0].resize(sz(factors));
        
        fac[0] = ifac[0] = 1;
        FOR(i,1,SZ+1) {
            cnt[i] = cnt[i-1];
            
            int I = i;
            F0R(j,sz(factors)) while (I % factors[j].f == 0) 
                I /= factors[j].f, cnt[i][j] ++;
                
            fac[i] = fac[i-1]*I;
            ifac[i] = inv(fac[i]);
        }
    }
    
    mi comb(int a, int b) {
        if (a < b || b < 0) return 0;
        mi tmp = fac[a]*ifac[b],MOD*ifac[a-b];
        F0R(i,sz(factors)) {
            int t = cnt[a][i]-cnt[a-b][i]-cnt[b][i];
            tmp *= exp(mi(factors[i].f,MOD),t);
        }
        return tmp;
    }
};