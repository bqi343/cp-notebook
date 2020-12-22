/** 
 * Description: computes the intersection point(s) of line segments $AB$, $CD$
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/segmentintersection
 */

#include "Point.h"

vP strict_isect(const Line& a, const Line& b) {
	T a0 = cross(a.f,a.s,b.f), a1 = cross(a.f,a.s,b.s); 
	T b0 = cross(b.f,b.s,a.f), b1 = cross(b.f,b.s,a.s); 
	if (sgn(a0)*sgn(a1) < 0 && sgn(b0)*sgn(b1) < 0) // strict intersection
		return {(b.s*a0-b.f*a1)/(a0-a1)};
	return {};
}

vP isect(const Line& a, const Line& b) { 
	vP v = strict_isect(a,b); if (sz(v)) return v;
	set<P> s;
	#define i(x,y) if (p_on_seg(x,y)) s.ins(x)
	i(a.f,b); i(a.s,b); i(b.f,a); i(b.s,a);
	return {all(s)};
}