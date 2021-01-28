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
	int ind = min_element(all(v))-begin(v);
	vi cand(sz(v)),C; iota(all(cand),0);
	sort(all(cand),[&](int a, int b) { 
		P x = v[a]-v[ind], y = v[b]-v[ind]; T t = cross(x,y);
		return t != 0 ? t > 0 : norm(x) < norm(y);
	});
	#define bad(x) cross(v[C[sz(C)-2]],v[C.bk],v[x]) <= 0
	each(t,cand) {
		while (sz(C) > 1 && bad(t)) C.pop_back();
		C.pb(t); } // if hull has > 1 point
	if (v[ind]!=v[C.bk])while(sz(C)>2&&bad(ind))C.pop_back();
	return C;
}
/**vP hull(const vP& v) {
	vi w = hullInd(v); vP res; each(t,w) res.pb(v[t]);
	return res; }*/
