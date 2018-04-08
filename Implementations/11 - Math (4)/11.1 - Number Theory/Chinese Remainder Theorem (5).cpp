/**
* Source: Own
* Verification: 
    * Kattis generalchineseremainder
    * POI 9 Rhyme
*/

namespace CRT {
    pl solveSimple(pl a, pl b) { // b.s divides a.s*x+a.f-b.f
        ll x = (b.f-a.f)*NT::inv(a.s,b.s) % b.s;
        ll ans = (a.s*x+a.f) % (a.s*b.s);
        if (ans < 0) ans += a.s*b.s;
        return {ans,a.s*b.s};
    }

    pl solve(pl a, pl b) {
        pl cur = {0,1};
        auto v = NT::fac(a.s); v.insert(v.end(),all(NT::fac(b.s)));
        for (auto z: v) {
            ll A = 1, B = 1; 
            while (a.s % z.f == 0) a.s /= z.f, A *= z.f;
            while (b.s % z.f == 0) b.s /= z.f, B *= z.f;
            if ((a.f-b.f)%min(A,B) != 0) return {-1,-1};
            
            if (A > B) cur = solveSimple(cur,{a.f%A,A});
            else cur = solveSimple(cur,{b.f%B,B});
        }
        return cur;
    }
};