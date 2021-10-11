/**
 * Description: Returns vertices of half-plane intersection.
   * A half-plane is the area to the left of a ray, which is defined
   * by a point \texttt{p} and a direction \texttt{dp}. 
   * Area of intersection should be sufficiently precise when all inputs
   * are integers with magnitude $\le 10^5$.
 * Time: O(N\log N)
 * Source: Own
 * Verification: 
	* https://open.kattis.com/problems/bigbrother 
	* https://icpc.kattis.com/problems/domes
 */

#include "AngleCmp.h"

struct Ray {
	P p, dp; // origin, direction
	P isect(const Ray& L) const {
		return p+dp*(cross(L.dp,L.p-p)/cross(L.dp,dp)); }
	bool operator<(const Ray& L) const {
		return angleCmp(dp,L.dp); }
};

vP halfPlaneIsect(V<Ray> _segs) {
	sor(_segs); // sort planes by angle
	V<Ray> segs; // remove parallel planes
	each(t,_segs) {
		if (!sz(segs) || segs.bk < t) { segs.pb(t); continue; }
		if (cross(t.dp,t.p-segs.bk.p) > 0) segs.bk = t;
	}
	auto bad = [&](const Ray& a, const Ray& b, const Ray& c) {
		P p1 = a.isect(b), p2 = b.isect(c);
		if (dot(p2-p1,b.dp) <= EPS) { // note: this EPS is required ...
			if (cross(a.dp,c.dp) <= 0) return 2; // isect(a,b,c) = empty
			return 1;
		}
		return 0; // isect(a,c) == isect(a,b,c)
	};
	#define reduce(t) \
		while (sz(poly) > 1) { \
			int b = bad(poly.at(sz(poly)-2),poly.bk,t); \
			if (b == 2) return {}; \
			if (b == 1) poly.pop_back(); \
			else break; \
		}
	deque<Ray> poly;
	each(t,segs) { reduce(t); poly.pb(t); }
	for(;;poly.pop_front()) {
		reduce(poly[0]);
		if (!bad(poly.bk,poly[0],poly[1])) break;
	}
	assert(sz(poly) >= 3); // if you reach this point, area should be nonzero
	vP poly_points; F0R(i,sz(poly)) poly_points.pb(poly[i].isect(poly[(i+1)%sz(poly)]));
	return poly_points;
}