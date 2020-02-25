/** 
 * Description: Given convex polygon with no three points collinear and a point 
 	* strictly outside of it, computes the lower and upper tangents.
 * Source: Own
 * Time: O(\log N)
 * Verification: tested
 */

#include "../Primitives/Point.h"

bool lower;
bool better(P a, P b, P c) { 
	T z = cross(a,b,c); 
	return lower ? z < 0 : z > 0; }
int tangent(const vP& a, P b) {
	if (sz(a) == 1) return 0;
	int lo, hi;
	if (better(b,a[0],a[1])) {
		lo = 0, hi = sz(a)-1;
		while (lo < hi) {
			int mid = (lo+hi+1)/2;
			if (better(b,a[0],a[mid])) lo = mid;
			else hi = mid-1;
		}
		lo = 0;
	} else {
		lo = 1, hi = sz(a);
		while (lo < hi) {
			int mid = (lo+hi)/2;
			if (!better(b,a[0],a[mid])) lo = mid+1;
			else hi = mid;
		}
		hi = sz(a);
	}
	while (lo < hi) {
		int mid = (lo+hi)/2;
		if (better(b,a[mid],a[(mid+1)%sz(a)])) lo = mid+1;
		else hi = mid;
	}
	return lo%sz(a);
}
pi tangents(const vP& a, P b) {
	lower = 1; int x = tangent(a,b); 
	lower = 0; int y = tangent(a,b); 
	return {x,y};
}