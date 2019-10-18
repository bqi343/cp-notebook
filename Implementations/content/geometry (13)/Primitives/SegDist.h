/**
 * Description: computes distance between $P$ and line segment $AB$
 * Source: own
 * Verification: https://open.kattis.com/problems/segmentdistance
 */

#include "lineDist.h"

T segDist(P p, P a, P b) { 
	if (dot(p-a,b-a) <= 0) return abs(p-a);
	if (dot(p-b,a-b) <= 0) return abs(p-b);
	return lineDist(p,a,b);
}