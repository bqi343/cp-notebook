/**
 * Description: Pollard's rho factors integers up to $2^{60}$. 
 	* Returns primes in sorted order.
 * Time: $O(N^{1/4})$ gcd calls, less for numbers with small factors
 * Source: KACTL
	* https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm
	* https://codeforces.com/contest/1033/submission/44009089 is faster
 * Verification: https://www.spoj.com/problems/FACT0/
 */

#include "PrimeSieve.h"
#include "MillerRabin.h"
#include "../Modular Arithmetic/ModMulLL.h"

Sieve<1<<20> S; // primes up to N^{1/3}
ul pollard(ul n) {
	auto f = [n](ul x) { return (modMul(x,x,n)+1)%n; };
	if (!(n&1)) return 2;
	for (ul i = 2;;++i) {
		ul x = i, y = f(x), p;
		while ((p = __gcd(n+y-x,n)) == 1) x = f(x), y = f(f(y));
		if (p != n) return p;
	}
}
vpl factor(ll d) {
	vpl res; 
	each(t,S.pr) {
		if ((ul)t*t > d) break;
		if (d%t == 0) {
			res.pb({t,0}); 
			while (d%t == 0) d /= t, res.bk.s ++;
		}
	}
	if (prime(d)) res.pb({d,1}), d = 1;
	if (d == 1) return res; // now a product of at most 2 primes
	ll c = pollard(d); d /= c; if (d > c) swap(d,c);
	if (c == d) res.pb({c,2});
	else res.pb({c,1}), res.pb({d,1});
	return res;
}
