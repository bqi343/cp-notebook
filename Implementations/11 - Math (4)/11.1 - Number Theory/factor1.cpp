/**
* Description: factors N in O(sqrtN) time
*/

namespace factor1 {
    vpl factor(ll x) { // x <= 10^{14} is fine
        vpl pri;
        
        for (int i = 2; i*i <= x; ++i) if (x % i == 0) {
            int t = 0;
            while (x % i == 0) x /= i, t ++;
            pri.pb({i,t});
        }
        
        if (x > 1) pri.pb({x,1});
        return pri;
    }

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