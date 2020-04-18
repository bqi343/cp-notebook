/**
 * Description: Prefix sums of some multiplicative functions.
 	* Solve for all square-free numbers in range, then fix.
 * Time: faster than $O(N^{2/3})$?
 * Source: Project Euler, https://oeis.org/A085731
 */

#include "Sieve.h"

ll pre0(ll n, int i) { // prod(primes) in factorization of x
	ll res = n*(n+1)/2; // assume all square-free
	for (;;++i) {
		ll p = S.pr[i], nn = n/p/p; if (!nn) break;
		for(ll coef=p*(p-1);nn;nn/=p)res-=coef*pre0(nn,i+1);
	}
	return res;
}
ll pre1(ll n, int i) { // gcd of x and arithmetic derivative 
	// p^e contributes p^e if e%p == 0 and p^{e-1} otherwise
	ll res = n; // assume all square-free
	for (;;++i) {
		ll p = S.pr[i], nn = n/p/p; if (!nn) break;
		ll lst = 1, mul = p*p;
		for (int e = 2; nn; mul *= p, nn /= p, ++e) {
			ll nex = mul; if (e%p) nex /= p;
			if (lst != nex) res += (nex-lst)*pre1(nn,i+1); 
			lst = nex;
		}
	}
	return res;
}