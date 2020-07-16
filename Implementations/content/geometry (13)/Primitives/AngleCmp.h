/**
 * Description: Sorts points in ccw order about origin in the same way as
 	* \texttt{atan2}, which returns real in $(-\pi,\pi]$ so points on 
 	* negative $x$-axis come last.
 * Verification: https://codeforces.com/contest/1284/submission/68175790
 	* https://codeforces.com/contest/1284/submission/68207607 
 	* (don't use atan2, weird stuff happens!)
 */

#include "Point.h"

int half(P x) { return x.s != 0 ? sgn(x.s) : -sgn(x.f); } // -1 if lower half, 0 if origin, 1 if upper half
bool angleCmp(P a, P b) { 
	int A = half(a), B = half(b);
	return A == B ? cross(a,b) > 0 : A < B; }

/** Usage: 
 	* vP v;
 	* sort(all(v),[](P a, P b) { return 
 		atan2(a.s,a.f) < atan2(b.s,b.f); });
 	* sort(all(v),angleCmp); // should give same result
*/