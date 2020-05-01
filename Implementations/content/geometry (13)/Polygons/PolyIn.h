/** 
 * Description: Tests whether point is inside, on, or outside of the 
 	* perimeter of a polygon. Both CW and CCW polygons are ok.
 * Time: O(N)
 * Verification: https://open.kattis.com/problems/pointinpolygon
 */

#include "../Primitives/Point.h"

string inPoly(const vP& p, P z) {
	int n = sz(p), ans = 0;
	F0R(i,n) {
		P x = p[i], y = p[(i+1)%n]; if (x.s > y.s) swap(x,y);
		if (onSeg(z,x,y)) return "on";
		ans ^= (x.s <= z.s && y.s > z.s && cross(z,x,y) > 0);
	}
	return ans ? "in" : "out";
}
