/**
 * Description: computes area + the center of mass of 
 	* a polygon with constant mass per unit area
 * Time: O(N)
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 * Verification: kattis polygonarea, VT HSPC 2018 Holiday Stars
 */

#include "Point.h"

T area(const vP& v) {
	T area = 0;
	F0R(i,sz(v)) {
		int j = (i+1)%sz(v); T a = cross(v[i],v[j]);
		area += a;
	}
	return std::abs(area)/2;
}
P centroid(const vP& v) { 
	P cen(0,0); T area = 0; // 2*signed area
	F0R(i,sz(v)) {
		int j = (i+1)%sz(v); T a = cross(v[i],v[j]);
		cen += a*(v[i]+v[j]); area += a;
	}
	return cen/area/(T)3;
}