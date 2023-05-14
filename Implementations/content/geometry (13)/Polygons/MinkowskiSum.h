/**
 * Description: Minkowski sum of two convex polygons given in CCW order.
 * Time: O(N)
 * Source: https://cp-algorithms.com/geometry/minkowski.html#implementation
 * Verification: 
   * MITPC
   * https://open.kattis.com/problems/roberthood
 */

#include "ConvexHull.h"

vP minkowski_sum(vP a, vP b) {
	if (sz(a) > sz(b)) swap(a, b);
	if (!sz(a)) return {};
	if (sz(a) == 1) {
		each(t, b) t += a.ft;
		return b;
	}
	rotate(begin(a), min_element(all(a)), end(a));
	rotate(begin(b), min_element(all(b)), end(b));
	a.pb(a[0]), a.pb(a[1]);
	b.pb(b[0]), b.pb(b[1]);
	vP result;
	int i = 0, j = 0;
	while (i < sz(a)-2 || j < sz(b)-2) {
		result.pb(a[i]+b[j]);
		T crs = cross(a[i+1]-a[i],b[j+1]-b[j]);
		i += (crs >= 0);
		j += (crs <= 0);
	}
	return result;
}

T diameter2(vP p) { // example application: squared diameter
	vP a = hull(p);
	vP b = a; each(t, b) t *= -1;
	vP c = minkowski_sum(a, b);
	T ret = 0; each(t, c) ckmax(ret, abs2(t));
	return ret;
}