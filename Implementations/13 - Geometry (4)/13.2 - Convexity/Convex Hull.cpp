/**
 * Description: Top-bottom convex hull
 * Source: Wikibooks
 * Verification: https://open.kattis.com/problems/convexhull
 */

// typedef ll T;

using namespace Point;

pair<vi,vi> ulHull(const vP& P) {
    vi p(sz(P)), u, l;
    iota(all(p), 0);
    sort(all(p), [&P](int a, int b) { return P[a] < P[b]; });
    trav(i,p) {
        #define ADDP(C, cmp) while (sz(C) > 1 && cross(\
            P[C[sz(C)-2]],P[C.back()],P[i]) cmp 0) C.pop_back(); C.pb(i);
        ADDP(u, >=); ADDP(l, <=);
    }
    return {u,l};
}

vi convexHull(const vP& P) {
    vi u,l; tie(u,l) = ulHull(P);
    if (sz(l) <= 1) return l;
    if (P[l[0]] == P[l[1]]) return {0};
    l.insert(end(l),rbegin(u)+1,rend(u)-1); return l;
}