/**
 * Description: square root of integer mod a prime
 * Time: O(\log^2(MOD))
 * Source: http://www.math.vt.edu/people/brown/class_homepages/shanks_tonelli.pdf
 * Verification: https://www.spoj.com/problems/CRYPTO1
 */

#include "Modular.h"

template<class T> T sqrt(modular<T> a) { 
	auto p = pow(a,(MOD-1)/2); 
	if (p != 1) return p == 0 ? 0 : -1; // check if 0 or no sqrt
	T s = MOD-1, e = 0; while (s % 2 == 0) s /= 2, e ++;
	// find non-square residue
	modular<T> n = 1; while (pow(n,(MOD-1)/2) == 1) n = (T)(n)+1; 
	auto x = pow(a,(s+1)/2), b = pow(a,s), g = pow(n,s);
	int r = e;
	while (1) {
		auto B = b; int m = 0; while (B != 1) B *= B, m ++;
		if (m == 0) return min((T)x,MOD-(T)x);
		F0R(i,r-m-1) g *= g;
		x *= g; g *= g; b *= g; r = m;
	}
}