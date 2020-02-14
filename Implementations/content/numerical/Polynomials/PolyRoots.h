/**
 * Source: KACTL
 * Description: Finds the real roots of a polynomial.
 * Usage: poly_roots({{2,-3,1}},-1e9,1e9) // solve x^2-3x+2 = 0
 * Time: O(N^2 \log(1/\epsilon))
 * Verification: https://open.kattis.com/problems/firingphaser
 */

#include "Poly.h"

typedef ld T;
poly polyRoots(poly p, T xmin, T xmax) {
	if (sz(p) == 2) { return {-p[0]/p[1]}; }
	auto dr = polyRoots(dif(p),xmin,xmax);
	dr.pb(xmin-1); dr.pb(xmax+1); sort(all(dr));
	poly ret;
	F0R(i,sz(dr)-1) {
		T l = dr[i], h = dr[i+1];
		bool sign = eval(p,l) > 0;
		if (sign^(eval(p,h) > 0)) {
			F0R(it,60) { // while (h-l > 1e-8)
				auto m = (l+h)/2, f = eval(p,m);
				if ((f <= 0) ^ sign) l = m;
				else h = m;
			}
			ret.pb((l+h)/2);
		}
	}
	return ret;
}
