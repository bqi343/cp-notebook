/**
 * Description: O(NlogN) line sweep to find two closest points
 * Source: Own
 * Verification: https://open.kattis.com/problems/closestpair2
 */

using namespace point;

pair<P,P> solve(vP v) {
    pair<ld,pair<P,P>> bes; bes.f = INF;
    set<P> S; int ind = 0;
    
    sort(all(v));
    F0R(i,sz(v)) {
        if (i && v[i] == v[i-1]) return {v[i],v[i]};
        
        for (; v[i].f-v[ind].f >= bes.f; ind++) 
            S.erase({v[ind].s,v[ind].f});
        
        for (auto it = S.ub({v[i].s-bes.f,INF});
            it != S.end() && it->f < v[i].s+bes.f;
            it = next(it)) {
            P t = {it->s,it->f};
            ckmin(bes,{abs(t-v[i]),{t,v[i]}});
        }
        
        S.insert({v[i].s,v[i].f});
    }
    
    return bes.s;
}