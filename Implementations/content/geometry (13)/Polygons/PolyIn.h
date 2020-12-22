/** 
 * Description: Tests whether point is inside, on, or outside of a polygon 
 	* (returns -1, 0, or 1). Both CW and CCW polygons are ok.
 * Time: O(N)
 * Verification: https://open.kattis.com/problems/pointinpolygon
 */

#include "../Primitives/Point.h"

int p_in_poly(const P& p, const vP& poly) {
	int n = sz(poly), ans = 0;
	F0R(i,n) {
		P x = poly[i], y = poly[(i+1)%n]; if (x.s > y.s) swap(x,y);
		if (p_on_seg(p,{x,y})) return 0;
		ans ^= (x.s <= p.s && p.s < y.s && cross(p,x,y) > 0);
	}
	return ans ? -1 : 1;
}