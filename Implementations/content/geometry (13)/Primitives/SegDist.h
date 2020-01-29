/**
 * Description: computes distance between $P$ and line (segment) $AB$
 * Source: own
 * Verification: https://open.kattis.com/problems/segmentdistance
 */

#include "Point.h"

T lineDist(P p, P a, P b) { 
	return abs(cross(p,a,b))/abs(a-b); }
T segDist(P p, P a, P b) { 
	if (dot(p-a,b-a) <= 0) return abs(p-a);
	if (dot(p-b,a-b) <= 0) return abs(p-b);
	return lineDist(p,a,b); }