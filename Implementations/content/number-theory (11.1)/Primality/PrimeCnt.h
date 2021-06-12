/**
 * Description: Counts number of primes up to $N$. Can also count 
 	* sum of primes. 
 * Time: $O(N^{3/4}/\log N)$, ~30ms for $N=10^{11}$.
 * Source: https://old.yosupo.jp/submission/7976
 * Verification: https://old.yosupo.jp/problem/counting_primes
 */

ll prime_cnt(const ll N) {
	if (N <= 1) return 0;
	if (N == 2) return 1;
	const int sq = (int)sqrtl(N);
	int s = (1+sq)/2; // 4 -> 1,3, 5 -> 1,3,5
	vi smalls(s); iota(all(smalls),0); // # odd primes <= 2*i+1
	vi roughs(s); F0R(i,s) roughs[i] = 2*i+1; // 3, 5, 7, ..., 2*s-1
	vl larges(s); F0R(i,s) larges[i] = (N/(2*i+1)-1)/2; // # odd primes <= N/roughs[i]
	vb skip(sq+1);
	auto divide = [&](ll n, ll d) { return int((db)n/d); };
	auto half = [&](int n) { return (n-1)/2; };
	int pc = 0;
	for (int p = 3; p <= sq; p += 2) if (!skip[p]) { // p is prime
		int q = p*p; if ((ll)q*q > N) break;
		skip[p] = 1; for (int i = q; i <= sq; i += 2*p) skip[i] = 1; // mark prime
		int ns = 0;
		F0R(k,s) {
			int i = roughs[k]; if (skip[i]) continue; // if roughs[k] is prime ?!
			ll d = (ll)i*p;
			larges[ns] = larges[k]+pc;
			larges[ns] -= d <= sq ? larges[smalls[d/2]-pc] : smalls[half(divide(N,d))];
			roughs[ns++] = i;
		}
		s = ns;
		for (int i = half(sq), j = (sq/p-1)|1; j >= p; j -= 2) {
			int c = smalls[j/2]-pc;
			for (int e = j*p/2; i >= e; --i) smalls[i] -= c;
		}
		++pc;
	} 
	// pc = # odd primes <= N^{1/4}
	// roughs now contains 1 and all primes in (N^{1/4},N^{1/2}]
	// larges[0] eliminates all composites with factor <= N^{1/4}
	FOR(k,1,s) larges[0] -= larges[k]; 
	larges[0] += (ll)(s+2*(pc-1))*(s-1)/2; // pc to s+pc-2
	// subtract larges[k] * (smth >= larges[k], divisible by no primes <= N^{1/4})
	// eliminates a*b where N^{1/4} < a,b

	// now larges is too small
	// what about a*b*c where N^{1/4} < a <= b <= c?
	// subtracted 3 times, need to add back 2

	// what about a=b<c
	// what about a<b=c: subtracted two times, need to add back one

	// a < b = c -> -1 (for q = a, - b)
	// a < b < c -> -2 (for q = a, - b, - c)
	// a = b < c -> -1

	FOR(l,1,s) {
		int q = roughs[l]; ll m = N/q; // q is prime
		int e = smalls[half(int(m/q))]-pc; if (e <= l) break; // last prime <= N/q/q
		FOR(k,l+1,e+1) larges[0] += smalls[half(divide(m,roughs[k]))]; // N/roughs[l]/roughs[k]
		larges[0] -= (ll)(e-l)*(pc+l-1); // # primes < q
	}
	return larges[0]+1; // add 1 for only even prime
}