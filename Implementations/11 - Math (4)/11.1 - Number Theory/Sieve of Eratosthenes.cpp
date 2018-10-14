/**
* Description: Tests primality up to n in O(nlog(logn)) 
* Source: ?
* Verification: https://open.kattis.com/problems/primesieve
*/

template<int SZ> struct sieve { 
	bitset<SZ> comp;
	vi pr;
	// int sp[SZ];

	sieve() {
		for (int i = 2; i*i <= SZ; ++i) if (!comp[i]) 
			for (int j = i*i; j <= SZ; j += i) comp[j] = 1;
		FOR(i,2,SZ) if (!comp[i]) pr.pb(i);
		
		/*FOR(i,2,SZ) { // O(N) sieve
			if (sp[i] == 0) { sp[i] = i; pr.pb(i); }
			for (int p : pr) {
				if (p > sp[i] || i*p >= SZ) break;
				sp[i*p] = p;
			}
		}*/
	}
};
