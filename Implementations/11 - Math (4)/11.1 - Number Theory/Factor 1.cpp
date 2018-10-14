/**
* Description: factors N in O(sqrtN) time
* Source: Own
* Verification: ?
*/

namespace factor1 {
    vpl factor(ll x) { // x <= 10^{14} is fine
        vpl pri;
        
        for (ll i = 2; i*i <= x; ++i) if (x % i == 0) {
            int t = 0;
            while (x % i == 0) x /= i, t ++;
            pri.pb({i,t});
        }
        
        if (x > 1) pri.pb({x,1});
        return pri;
    }

    /* Note: 
    * number of operations needed s.t. 
    *                phi(phi(...phi(n)...))=1 
    * is O(log n).
    * Euler's theorem: a^{\phi(p)}\equiv 1 (mod p), gcd(a,p)=1*/
    ll phi(ll x) {
        for (auto a: factor(x)) x /= a.f, x *= a.f-1; 
        return x;
    }

    void trav(vpl& v, vl& V, int ind, ll cur) {
        if (ind == sz(v)) V.pb(cur);
        else {
            ll mul = 1;
            F0R(i,v[ind].s+1) {
                trav(v,V,ind+1,cur*mul);
                mul *= v[ind].f;
            }
        }
    }

    vl getDivi(ll x) {
        vpl v = factor(x); vl V;
        trav(v,V,0,1);
        sort(all(V));
        return V;
    }
}

using namespace factor1;