/**
 * Description: rotating caliphers, gives greatest distance between two points in $P$
 * Time: $O(N)$ given convex hull
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/roberthood
 */

#include "ConvexHull (13.2).h"

db diameter(vP P) { 
	P = hull(P);
	int n = sz(P), ind = 1; db ans = 0;
	if (n > 1) F0R(i,n) for (int j = (i+1)%n;;ind = (ind+1)%n) {
		ckmax(ans,abs(P[i]-P[ind]));
		if (cross(P[j]-P[i],P[(ind+1)%n]-P[ind]) <= 0) break;
	}
	return ans;
}
