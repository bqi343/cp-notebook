/**
 * Description: Graham Scan
 * Time: O(N\log N)
 * Source: Own
 * Verification:
	* https://open.kattis.com/problems/convexhull
 */

#include "../Primitives/Point.h"

/// typedef ll T;
vi hullInd(const vP& v) {
	int ind = int(min_element(all(v))-begin(v));
	vi cand, C{ind}; F0R(i,sz(v)) if (v[i] != v[ind]) cand.pb(i);
	sort(all(cand),[&](int a, int b) { // sort by angle, tiebreak by distance
		P x = v[a]-v[ind], y = v[b]-v[ind]; T t = cross(x,y);
		return t != 0 ? t > 0 : norm(x) < norm(y); }); 
	each(c,cand) {
		while (sz(C) > 1 && cross(v[end(C)[-2]],v[C.bk],v[c]) <= 0) C.pop_back();
		C.pb(c); }
	return C;
}
/**vP hull(const vP& v) {
	vi w = hullInd(v); vP res; each(t,w) res.pb(v[t]);
	return res; }*/
