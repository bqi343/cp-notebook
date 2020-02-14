/**
 * Description: \texttt{lineHull} accepts line and ccw convex polygon. If all vertices in poly 
 	* lie to one side of the line, returns a vector of closest vertices to line as well as 
 	* orientation of poly with respect to line ($\pm 1$ for above/below). Otherwise, returns 
 	* the range of vertices that lie on or below the line. \texttt{extrVertex} returns the point 
 	* of a hull with the max projection onto a line.
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/geometry/LineHullIntersection.h
 * Time: O(\log N)
 * Verification: tested
 */

#include "../Primitives/Point.h"

typedef array<P,2> Line;
#define cmp(i,j) sgn(-dot(dir,poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i+1,i) >= 0 && cmp(i,i-1+n) < 0
int extrVertex(const vP& poly, P dir) {
	int n = sz(poly), lo = 0, hi = n;
	if (extr(0)) return 0;
	while (lo+1 < hi) {
		int m = (lo+hi)/2;
		if (extr(m)) return m;
		int ls = cmp(lo+1,lo), ms = cmp(m+1,m);
		(ls < ms || (ls == ms && ls == cmp(lo,m)) ? hi : lo) = m;
	}
	return lo;
}
vi same(Line line, const vP& poly, int a) { 
	// points on same parallel as a
	int n = sz(poly); P dir = perp(line[0]-line[1]); 
	if (cmp(a+n-1,a) == 0) return {(a+n-1)%n,a};
	if (cmp(a,a+1) == 0) return {a,(a+1)%n};
	return {a};
}
#define cmpL(i) sgn(cross(line[0],line[1],poly[i]))
pair<int,vi> lineHull(Line line, const vP& poly) {
	int n = sz(poly); assert(n>1);
	int endA = extrVertex(poly,perp(line[0]-line[1])); // lowest
	if (cmpL(endA) >= 0) return {1,same(line,poly,endA)};
	int endB = extrVertex(poly,perp(line[1]-line[0])); // highest
	if (cmpL(endB) <= 0) return {-1,same(line,poly,endB)}; 
	array<int,2> res;
	F0R(i,2) {
		int lo = endA, hi = endB; if (hi < lo) hi += n;
		while (lo < hi) {
			int m = (lo+hi+1)/2;
			if (cmpL(m%n) == cmpL(endA)) lo = m;
			else hi = m-1;
		}
		res[i] = lo%n; swap(endA,endB);
	}
	if (cmpL((res[0]+1)%n) == 0) res[0] = (res[0]+1)%n;
	return {0,{(res[1]+1)%n,res[0]}};
}
