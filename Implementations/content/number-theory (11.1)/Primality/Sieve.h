/**
 * Description: Tests primality up to $SZ$. Runs faster if only
 	* odd indices are stored.
 * Time: O(SZ\log\log SZ) or O(SZ)
 * Source: KACTL 
 * Verification: https://open.kattis.com/problems/primesieve
 */

template<int SZ> struct Sieve { 
	bitset<SZ> pri; vi pr;
	Sieve() { // cum[i] = # of primes up to i
		pri.set(); pri[0] = pri[1] = 0;
		for (int i = 4; i < SZ; i += 2) pri[i] = 0;
		for (int i = 3; i*i < SZ; i += 2) if (pri[i])
			for (int j = i*i; j < SZ; j += i*2) pri[j] = 0;
		F0R(i,SZ) if (pri[i]) pr.pb(i);
	}
	/*int sp[SZ]; // smallest prime that divides
	Sieve() { // above is faster
		memset(sp,0,sizeof sp);
		FOR(i,2,SZ) { 
			if (sp[i] == 0) sp[i] = i, pr.pb(i); 
			each(p,pr) {
				if (p > sp[i] || i*p >= SZ) break;
				sp[i*p] = p;
			}
		}
	}*/
};
Sieve<320000> S;
