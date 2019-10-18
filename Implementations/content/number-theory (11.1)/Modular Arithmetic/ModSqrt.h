/**
 * Description: find sqrt of integer mod a prime
 * Time: ?
 * Source: http://www.math.vt.edu/people/brown/class_homepages/shanks_tonelli.pdf
 * Verification: https://www.spoj.com/problems/CRYPTO1
 */

#include "Modular.h"

template<class T> T sqrt(modular<T> a) { 
	auto p = pow(a,(MOD-1)/2); if (p != 1) return p == 0 ? 0 : -1; // check if zero or does not have sqrt
	T s = MOD-1, e = 0; while (s % 2 == 0) s /= 2, e ++;
	modular<T> n = 1; while (pow(n,(MOD-1)/2) == 1) n = (T)(n)+1; // find non-square residue

	auto x = pow(a,(s+1)/2), b = pow(a,s), g = pow(n,s);
	int r = e;
	while (1) {
		auto B = b; int m = 0; while (B != 1) B *= B, m ++;
		if (m == 0) return min((T)x,MOD-(T)x);
		F0R(i,r-m-1) g *= g;
		x *= g; g *= g; b *= g; r = m;
	}
}

/* Explanation:
 * Initially, x^2=ab, ord(b) = 2^m, ord(g) = 2^r where m<r
 * g = g^{2^{r-m-1}} -> ord(g) = 2^{m+1}
 * if x'=x*g, then b' = b*g^2
		(b')^{2^{m-1}} = (b*g^2)^{2^{m-1}}
					   = b^{2^{m-1}}*g^{2^m}
					   = -1*-1
					   = 1
	-> ord(b')|ord(b)/2
 * m decreases by at least one each iteration
 */