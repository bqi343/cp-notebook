/**
* Description: O(NlogN) line sweep to find two closest points
* Source: Own
* Verification: https://open.kattis.com/problems/closestpair2
*/

ld dist(pd a, pd b) {
    return sqrt(pow(a.f-b.f,2)+pow(a.s-b.s,2));
}

pair<pd,pd> solve(vector<pd> v) {
    pair<ld,pair<pd,pd>> bes; bes.f = INF;
    
    set<pd> S;
    int ind = 0;
    
    sort(all(v));
    F0R(i,sz(v)) {
        if (i && v[i] == v[i-1]) return {v[i],v[i]};
        
        while (v[i].f-v[ind].f >= bes.f) {
            S.erase({v[ind].s,v[ind].f});
            ind ++;
        }
        
        for (auto it = S.ub({v[i].s-bes.f,INF});
            it != S.end() && it->f < v[i].s+bes.f;
            it = next(it)) {
            pd t = {it->s,it->f};
            bes = min(bes,{dist(t,v[i]),{t,v[i]}});
        }
        
        S.insert({v[i].s,v[i].f});
    }
    
    return bes.s;
}