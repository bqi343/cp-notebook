/**
 * Description: Factors integers up to $2^{60}$
 * Time: ?
 * Source: KACTL
	* https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
	* https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm
	* https://codeforces.com/contest/1033/submission/44009089 is faster
 * Verification: https://www.spoj.com/problems/FACT0/
 */

#include "PrimeSieve.h"

Sieve<1<<20> S = Sieve<1<<20>(); // should take care of all primes up to n^(1/3)

bool millerRabin(ll p) { // test primality
	if (p == 2) return true;
	if (p == 1 || p % 2 == 0) return false;
	ll s = p - 1; while (s % 2 == 0) s /= 2;
	F0R(i,30) { // strong liar with probability <= 1/4
		ll a = rand() % (p - 1) + 1, tmp = s;
		ll mod = mod_pow(a, tmp, p);
		while (tmp != p - 1 && mod != 1 && mod != p - 1) {
			mod = mod_mul(mod, mod, p);
			tmp *= 2;
		}
		if (mod != p - 1 && tmp % 2 == 0) return false;
	}
	return true;
}

ll f(ll a, ll n, ll &has) { return (mod_mul(a, a, n) + has) % n; }

vpl pollardsRho(ll d) {
	vpl res;
	auto& pr = S.pr;
	for (int i = 0; i < sz(pr) && pr[i]*pr[i] <= d; i++) if (d % pr[i] == 0) {
		int co = 0; while (d % pr[i] == 0) d /= pr[i], co ++;
		res.pb({pr[i],co});
	}
	if (d > 1) { // d is now a product of at most 2 primes.
		if (millerRabin(d)) res.pb({d,1});
		else while (1) {
			ll has = rand() % 2321 + 47;
			ll x = 2, y = 2, c = 1;
			for (; c == 1; c = __gcd(abs(x-y), d)) {
				x = f(x, d, has);
				y = f(f(y, d, has), d, has);
			} // should cycle in ~sqrt(smallest nontrivial divisor) turns 
			if (c != d) {
				d /= c; if (d > c) swap(d,c);
				if (c == d) res.pb({c,2});
				else res.pb({c,1}), res.pb({d,1});
				break;
			}
		}
	}
	return res;
}