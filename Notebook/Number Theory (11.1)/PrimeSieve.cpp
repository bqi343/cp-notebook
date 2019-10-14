/**
 * Description: Tests primality up to n in O(nlog(logn)) 
 * Source: KACTL 
 * Verification: https://open.kattis.com/problems/primesieve
 */

template<int SZ> struct Sieve { 
	bitset<SZ> isprime;
	vi pr;

	Sieve() {
		isprime.set(); isprime[0] = isprime[1] = 0;
		for (int i = 4; i < SZ; i += 2) isprime[i] = 0;
		for (int i = 3; i*i < SZ; i += 2) if (isprime[i])
			for (int j = i*i; j < SZ; j += i*2) isprime[j] = 0;
		vi pr;
		FOR(i,2,SZ) if (isprime[i]) pr.pb(i);
	}

	/* linear time sieve, not actually faster
	int sp[SZ];
	void sieveLinear() {
		memset(sp,0,sizeof sp);
		FOR(i,2,SZ) { // O(N) sieve
			if (sp[i] == 0) { sp[i] = i; pr.pb(i); }
			trav(p,pr) {
				if (p > sp[i] || i*p >= SZ) break;
				sp[i*p] = p;
			}
		}
	} 
	*/
};