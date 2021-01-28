/**
 * Description: Deterministic primality test, works up to $2^{64}$.
 	* For larger numbers, extend $A$ randomly.
 * Source: KACTL
	* https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
 * Verification: https://www.spoj.com/problems/FACT0/
 */

#include "ModMulLL.h"

bool prime(ul n) { // not ll!
	if (n < 2 || n % 6 % 4 != 1) return n-2 < 2;
	ul A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n>>s;
	each(a,A) {   // ^ count trailing zeroes
		ul p = modPow(a,d,n), i = s;
		while (p != 1 && p != n-1 && a%n && i--) p = modMul(p,p,n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}
