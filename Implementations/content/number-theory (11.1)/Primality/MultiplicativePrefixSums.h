/**
 * Description: $\sum_{i=1}^Nf(i)$ where $f(i)=\prod \texttt{val}[e]$ for each $p^e$
    * in the factorization of $i$. Must satisfy $\texttt{val}[1]=1$.
    * Generalizes to any multiplicative function with $f(p)=p^{\text{fixed power}}$.
 * Time: $O(\sqrt N)$
 * Source: Project Euler, https://oeis.org/A085731
 * Verification: https://www.codechef.com/problems/TABRARRAY
 */

#include "Sieve.h"

vmi val;
mi get_prefix(ll N, int p = 0) {
	mi ans = N;
	for (; S.primes.at(p) <= N / S.primes.at(p); ++p) {
		ll new_N = N / S.primes.at(p) / S.primes.at(p);
		for (int idx = 2; new_N; ++idx, new_N /= S.primes.at(p)) {
			ans += (val.at(idx) - val.at(idx - 1))
					 * get_prefix(new_N, p + 1);
		}
	}
	return ans;
}