/** 
 * Description: tests whether a point is inside, on, or outside the perimeter of any polygon
 * Time: O(N)
 * Verification: https://open.kattis.com/problems/pointinpolygon
 */

#include "Point.h"

string inPoly(const vP& p, P z) {
	int n = sz(p), ans = 0;
	F0R(i,n) {
		P x = p[i], y = p[(i+1)%n];
		if (onSeg(z,x,y)) return "on";
		if (x.s > y.s) swap(x,y);
		if (x.s <= z.s && y.s > z.s && cross(z,x,y) > 0) ans ^= 1;
	}
	return ans ? "in" : "out";
}
