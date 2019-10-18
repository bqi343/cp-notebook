/** 
 * Description: computes the intersection point(s) of lines $AB$, $CD;$
 	* returns {-1,{0,0}} if infinitely many, {0,{0,0}} if none, 
 	* {1,x} if x is the unique point
 * Source: KACTL
 * Verification: ?
 */

#include "Point.h"

P extension(P a, P b, P c, P d) { 
	T x = cross(a,b,c), y = cross(a,b,d);
	return (d*x-c*y)/(x-y);
}
pair<int,P> lineIntersect(P a, P b, P c, P d) {
	if (cross(b-a,d-c) == 0) return {-(cross(a,c,d) == 0),P(0,0)};
	return {1,extension(a,b,c,d)};
}