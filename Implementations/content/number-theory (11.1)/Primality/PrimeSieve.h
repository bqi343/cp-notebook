/**
 * Description: tests primality up to n
 * Time: O(N\log\log N)
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
};