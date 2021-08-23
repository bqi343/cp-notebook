/**
 * Description: square root of integer mod a prime, -1 if doesn't exist.
 * Time: O(\log^2(MOD))
 * Source: http://www.math.vt.edu/people/brown/class_homepages/shanks_tonelli.pdf
 * Verification: https://www.spoj.com/problems/CRYPTO1
 */

#include "ModInt.h"

using T = int;
T sqrt(mi a) { 
	mi p = pow(a,(MOD-1)/2); 
	if (p.v != 1) return p.v == 0 ? 0 : -1;
	/// check if 0 or no sqrt
	T s = MOD-1; int r = 0; while (s%2 == 0) s /= 2, ++r;
	mi n = 1; while (pow(n,(MOD-1)/2).v != 1) n = T(n)+1; 
	// n non-square, ord(g)=2^r, ord(b)=2^m, ord(g)=2^r, m<r
	for (mi x = pow(a,(s+1)/2), b = pow(a,s), g = pow(n,s);;) {
		if (b.v == 1) return min(x.v,MOD-x.v); // x^2=ab
		int m = 0; for (mi t = b; t.v != 1; t *= t) ++m;
		rep(r-m-1) g *= g; // ord(g)=2^{m+1}
		x *= g, g *= g, b *= g, r = m; // ord(g)=2^m, ord(b)<2^m
	}
}
