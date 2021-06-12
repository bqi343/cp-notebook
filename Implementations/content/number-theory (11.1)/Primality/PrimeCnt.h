/**
 * Description: Counts number of primes up to $N$. Can also count 
 	* sum of primes. 
 * Time: $O(N^{3/4}/\log N)$, ~30ms for $N=10^{11}$.
 * Source: https://old.yosupo.jp/submission/7976
 * Verification: https://old.yosupo.jp/problem/counting_primes
 */

ll prime_cnt(const ll N) {
	// here we only consider odd primes
	if (N <= 1) return 0;
	if (N == 2) return 1;
	const int sq = (int)sqrtl(N);
	int s = (1+sq)/2;

	vi small_ans(s); iota(all(small_ans),0); 
	// small[i] = # odd primes <= 2*i+1
	// sq=4 -> 1,3, sq=5 -> 1,3,5

	vi roughs(s); vl large_ans(s); 
	F0R(i,s) {
		roughs[i] = 2*i+1; // 3, 5, 7, ..., 2*s-1
		large_ans[i] = (N/roughs[i]-1)/2; 
		// large_ans[i] = # of prime candidates <= N/roughs[i]
		// a number is a prime candidate if none of primes found so far are a proper factor
		// initially the prime candidates are 3,5,7,...,N/roughs[i]
	}
	auto divide = [&](ll n, ll d) { return int(n/d); };
	auto half = [&](int n) { return (n-1)/2; };
	vb skip(sq+1);
	int pc = 0; // # odd primes <= N^{1/4}
	for (int p = 3; p <= sq; p += 2) if (!skip[p]) { // iterate over all p <= N^{1/4} prime
		int q = p*p; if ((ll)q*q > N) break;
		skip[p] = 1; for (int i = q; i <= sq; i += 2*p) skip[i] = 1; // mark odd multiples of p as composite
		int ns = 0;
		F0R(k,s) {
			int i = roughs[k]; if (skip[i]) continue; 
			// we only care about the answer when i is not divisible by any found primes so far
			ll d = (ll)i*p;
			large_ans[ns] = large_ans[k]+pc; 
			// cands(step+1,x) = cands(step,x)-(cands(step,x/prime[step])-pc)
			large_ans[ns] -= d <= sq ? large_ans[small_ans[d/2]-pc] : small_ans[half(divide(N,d))];
			roughs[ns++] = i;
		}
		s = ns;
		for (int i = half(sq), j = (sq/p-1)|1; j >= p; j -= 2) {
			int c = small_ans[j/2]-pc;
			for (int e = j*p/2; i >= e; --i) small_ans[i] -= c;
		}
		++pc;
	} 
	// roughs now contains 1 and all primes in (N^{1/4},N^{1/2}]
	// large_ans[0] contains everything with no prime factor <= N^{1/4} (i.e., it overcounts)

	// now we need to subtract out the overcounts
	// several cases (all are of form a*b or a*b*c where N^{1/4} <= a <= b <= c are primes)
		// a*b where b <= N^{1/2}
		// a*b where N^{1/4} < a, N^{1/2} < b
		// a*b*c where a<b<c<=N^{1/2}
		// a*b*c where a=b<c<=N^{1/2}
		// a*b*c where a<b=c<=N^{1/2}
		// a*b*c where a=b=c<=N^{1/2}

	// first we deal with both a*b cases, but we don't correctly correctly deal with a*b*c cases
	FOR(k,1,s) large_ans[0] -= large_ans[k]; // subtract multiples of roughs[k], which is a prime in (N^{1/4},N^{1/2}]
	large_ans[0] += (ll)(s+2*(pc-1))*(s-1)/2; // = sum(pc...s+pc-2)
	// correctly deal with a*b where b <= N^{1/2}

	// what about a=b<c
	// what about a<b=c: subtracted two times, need to add back one

	// a < b = c -> -1 (for q = a, - b)
	// a < b < c -> -2 (for q = a, - b, - c)
	// a = b < c -> -1

	FOR(l,1,s) { // iterate over all primes q > N^{1/4} such that q*q*q <= N
		int q = roughs[l]; ll m = N/q; // q is prime in (N^{1/4},N^{1/2}]
		int e = small_ans[half(int(m/q))]-pc; if (e <= l) break;
		FOR(k,l+1,e+1) large_ans[0] += small_ans[half(divide(m,roughs[k]))]; // N/roughs[l]/roughs[k]
		large_ans[0] -= (ll)(e-l)*(pc+l-1); // # primes < q
	}
	return large_ans[0]+1; // add 1 for prime=2
}