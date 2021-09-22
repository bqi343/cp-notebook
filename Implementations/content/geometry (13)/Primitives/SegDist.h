/**
 * Description: computes distance between $P$ and line (segment) $AB$
 * Source: own
 * Verification: https://open.kattis.com/problems/segmentdistance
 */

#include "Point.h"

T lineDist(const P& p, const Line& l) { 
	return abs(cross(p,l.f,l.s))/abs(l.f-l.s); }
T segDist(const P& p, const Line& l) {
	if (dot(l.f,p,l.s) <= 0) return abs(p-l.f);
	if (dot(l.s,p,l.f) <= 0) return abs(p-l.s);
	return lineDist(p,l); }