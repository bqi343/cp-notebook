/**
 * Description: Returns vertices of half-plane intersection.
   * A half-plane is the area to the left of a ray, which is defined
   * by a point \texttt{p} and a direction \texttt{dp}. 
   * Area of intersection should be sufficiently precise when all inputs
   * are integers with magnitude $\le 10^5$. Probably works with floating 
   * point too (but not well tested). Assumes intersection is bounded 
   * (easiest way to ensure this is to uncomment the code below).
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

vP halfPlaneIsect(V<Ray> rays_orig) {
	// int DX = 1e9, DY = 1e9; // bound input by rectangle [0,DX] x [0,DY]
	// rays_orig.pb({P{0,0},P{1,0}});
	// rays_orig.pb({P{DX,0},P{0,1}});
	// rays_orig.pb({P{DX,DY},P{-1,0}});
	// rays_orig.pb({P{0,DY},P{0,-1}});
	sor(rays_orig); // sort rays by angle
	V<Ray> rays; // without parallel rays
	each(t,rays_orig) {
		if (!sz(rays) || rays.bk < t) { rays.pb(t); continue; }
		// WARNING: use cross(rays.bk,t) > EPS instead of rays.bk < t if working with floating point dp
		if (cross(t.dp,t.p-rays.bk.p) > 0) rays.bk = t; // last two rays are parallel, remove one
	}
	auto bad = [&](const Ray& a, const Ray& b, const Ray& c) {
		P p1 = a.isect(b), p2 = b.isect(c);
		if (dot(p2-p1,b.dp) <= EPS) { // this EPS is required ...
			if (cross(a.dp,c.dp) <= 0) return 2; // isect(a,b,c) = empty
			return 1; // isect(a,c) == isect(a,b,c), remove b
		}
		return 0; // all the rays matter
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
	assert(sz(poly) >= 3); // if you reach this point, area should be nonzero
	vP poly_points; F0R(i,sz(poly)) 
		poly_points.pb(poly[i].isect(poly[(i+1)%sz(poly)]));
	return poly_points;
}