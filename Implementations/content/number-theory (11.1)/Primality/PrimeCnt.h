/**
 * Description: Counts number of primes up to $N$. Can also count 
 	* sum of primes. 
 * Time: $O(N^{3/4}/\log N)$, ~60ms for $N=10^{11}$, ~2.5s for $N=10^{13}$
 * Source: https://old.yosupo.jp/submission/7976
 * Verification: https://old.yosupo.jp/problem/counting_primes
 */

ll count_primes(ll N) { // count_primes(1e13) == 346065536839
	if (N <= 1) return 0;
	int sq = (int)sqrt(N);
	vl big_ans((sq+1)/2), small_ans(sq+1);
	FOR(i,1,sq+1) small_ans[i] = (i-1)/2;
	F0R(i,sz(big_ans)) big_ans[i] = (N/(2*i+1)-1)/2;
	vb skip(sq+1); int prime_cnt = 0;
	for (int p = 3; p <= sq; p += 2) if (!skip[p]) { // primes
		for (int j = p; j <= sq; j += 2*p) skip[j] = 1;
		F0R(j,min((ll)sz(big_ans),(N/p/p+1)/2)) {
			ll prod = (ll)(2*j+1)*p;
			big_ans[j] -= (prod > sq ? small_ans[(double)N/prod]
						 : big_ans[prod/2])-prime_cnt;
		}
		for (int j = sq, q = sq/p; q >= p; --q) for (;j >= q*p;--j) 
			small_ans[j] -= small_ans[q]-prime_cnt;
		++prime_cnt;
	}
	return big_ans[0]+1;
}