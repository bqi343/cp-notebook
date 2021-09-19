/** 
 * Description: computes the intersection point(s) of line (segments) $a$ and $b$
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/segmentintersection
 */

#include "Point.h"

// {unique intersection point} if it exists
// {b.f,b.s} if input lines are the same
// empty if lines do not intersect
vP lineIsect(const Line& a, const Line& b) {
	T a0 = cross(a.f,a.s,b.f), a1 = cross(a.f,a.s,b.s); 
	if (a0 == a1) return a0 == 0 ? vP{b.f,b.s} : vP{};
	return {(b.s*a0-b.f*a1)/(a0-a1)};
}

// point in interior of both segments a and b, if it exists
vP strictIsect(const Line& a, const Line& b) {
	T a0 = cross(a.f,a.s,b.f), a1 = cross(a.f,a.s,b.s); 
	T b0 = cross(b.f,b.s,a.f), b1 = cross(b.f,b.s,a.s); 
	if (sgn(a0)*sgn(a1) < 0 && sgn(b0)*sgn(b1) < 0)
		return {(b.s*a0-b.f*a1)/(a0-a1)};
	return {};
}

// intersection of segments, a and b may be degenerate
vP segIsect(const Line& a, const Line& b) { 
	vP v = strictIsect(a,b); if (sz(v)) return v;
	set<P> s;
	#define i(x,y) if (onSeg(x,y)) s.ins(x)
	i(a.f,b); i(a.s,b); i(b.f,a); i(b.s,a);
	return {all(s)};
}
