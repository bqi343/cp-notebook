/** 
 * Description: computes the intersection point(s) of line segments $AB$, $CD$
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/segmentintersection
 */

#include "Point.h"

vP segIntersect(P a, P b, P c, P d) { 
	T x = cross(a,b,c), y = cross(a,b,d); 
	T X = cross(c,d,a), Y = cross(c,d,b); 
	if (sgn(x)*sgn(y) < 0 && sgn(X)*sgn(Y) < 0) return {(d*x-c*y)/(x-y)};
	set<P> s;
	if (onSeg(a,c,d)) s.insert(a);
	if (onSeg(b,c,d)) s.insert(b);
	if (onSeg(c,a,b)) s.insert(c);
	if (onSeg(d,a,b)) s.insert(d);
	return {all(s)};
}