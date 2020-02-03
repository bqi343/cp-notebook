/** 
 * Description: computes the intersection point(s) of line segments $AB$, $CD$
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/segmentintersection
 */

#include "Point.h"

vP segIsect(P a, P b, P c, P d) { 
	T x = cross(a,b,c), y = cross(a,b,d); 
	T X = cross(c,d,a), Y = cross(c,d,b); 
	if (sgn(x)*sgn(y) < 0 && sgn(X)*sgn(Y) < 0) 
		return {(d*x-c*y)/(x-y)}; // interior
	set<P> s;
	#define i(a,b,c) if (onSeg(a,b,c)) s.insert(a)
	i(a,c,d); i(b,c,d); i(c,a,b); i(d,a,b);
	return {all(s)};
}