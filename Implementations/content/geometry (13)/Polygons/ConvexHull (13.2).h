/**
 * Description: top-bottom convex hull
 * Time: O(N\log N)
 * Source: Wikibooks, KACTL
 * Verification:
	* https://open.kattis.com/problems/convexhull
 */

#include "../Primitives/Point.h"

/// typedef ll T;
pair<vi,vi> ulHull(const vP& v) {
	vi p(sz(v)), u, l; iota(all(p), 0);
	sort(all(p), [&v](int a, int b) { return v[a] < v[b]; });
	each(i,p) {
		#define ADDP(C, cmp) while (sz(C) > 1 && cross(\
			v[C[sz(C)-2]],v[C.bk],v[i]) cmp 0) C.pop_back(); C.pb(i);
		ADDP(u, >=); ADDP(l, <=);
	}
	return {u,l};
}
vi hullInd(const vP& v) {
	vi u,l; tie(u,l) = ulHull(v); if (sz(l) <= 1) return l;
	if (v[l[0]] == v[l[1]]) return {0};
	l.insert(end(l),1+rall(u)-1); return l;
}
vP hull(const vP& v) {
	vi w = hullInd(v); vP res; each(t,w) res.pb(v[t]);
	return res; }
