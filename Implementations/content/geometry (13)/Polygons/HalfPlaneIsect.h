/**
 * Description: Returns vertices of half-plane intersection.
   * A half-plane is the area to the left of a ray, which is defined
   * by a point \texttt{p} and a direction \texttt{dp}. 
   * Area of intersection should be sufficiently precise when all inputs
   * are integers with magnitude $\le 10^5$. Intersection must be bounded.
   * Probably works with floating point too (but EPS might need to be adjusted?).
 * Time: O(N\log N)
 * Source: Own
 * Verification: 
	* https://open.kattis.com/problems/bigbrother 
	* https://icpc.kattis.com/problems/domes
	* https://codeforces.com/gym/100962 B
 */

#include "AngleCmp.h"

struct Ray {
	P p, dp; // origin, direction
	P isect(const Ray& L) const {
		return p+dp*(cross(L.dp,L.p-p)/cross(L.dp,dp)); }
	bool operator<(const Ray& L) const {
		return angleCmp(dp,L.dp); }
};

vP halfPlaneIsect(V<Ray> rays, bool add_bounds = false) {
	if (add_bounds) { // bound input by rectangle [0,DX] x [0,DY]
		int DX = 1e9, DY = 1e9;
		rays.pb({P{0,0},P{1,0}});
		rays.pb({P{DX,0},P{0,1}});
		rays.pb({P{DX,DY},P{-1,0}});
		rays.pb({P{0,DY},P{0,-1}});
	}
	sor(rays); // sort rays by angle
	{ // remove parallel rays
		V<Ray> nrays;
		each(t,rays) {
			if (!sz(nrays) || cross(nrays.bk.dp,t.dp) > EPS) { nrays.pb(t); continue; }
			// last two rays are parallel, keep only one
			if (cross(t.dp,t.p-nrays.bk.p) > 0) nrays.bk = t;
		}
		swap(rays, nrays);
	}
	auto bad = [&](const Ray& a, const Ray& b, const Ray& c) {
		P p1 = a.isect(b), p2 = b.isect(c);
		if (dot(p2-p1,b.dp) <= EPS) { /// this EPS is required ...
			if (cross(a.dp,c.dp) <= 0) return 2; // isect(a,b,c) = empty
			return 1; // isect(a,c) == isect(a,b,c)
		}
		return 0; // all three rays matter
	};
	#define reduce(t) \
		while (sz(poly) > 1) { \
			int b = bad(poly.at(sz(poly)-2),poly.bk,t); \
			if (b == 2) return {}; \
			if (b == 1) poly.pop_back(); \
			else break; \
		}
	deque<Ray> poly;
	each(t,rays) { reduce(t); poly.pb(t); }
	for(;;poly.pop_front()) {
		reduce(poly[0]);
		if (!bad(poly.bk,poly[0],poly[1])) break;
	}
	assert(sz(poly) >= 3); // expect nonzero area
	vP poly_points; F0R(i,sz(poly)) 
		poly_points.pb(poly[i].isect(poly[(i+1)%sz(poly)]));
	return poly_points;
}