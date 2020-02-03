/** 
 * Description: Computes the intersection point(s) of lines $AB$, $CD.$
 	* Returns $\{-1,\{0,0\}\}$ if infinitely many, $\{0,\{0,0\}\}$ if none, 
 	* $\{1,x\}$ if $x$ is the unique point.
 * Source: KACTL
 * Verification: ?
 */

#include "Point.h"


P ext(P a, P b, P c, P d) { // extension in asymptote
	T x = cross(a,b,c), y = cross(a,b,d);
	return (d*x-c*y)/(x-y); }
pair<int,P> lineIsect(P a, P b, P c, P d) { 
	return cross(b-a,d-c) == 0 ? mp(-(cross(a,c,d) == 0),P()) 
	: mp(1,ext(a,b,c,d)); }