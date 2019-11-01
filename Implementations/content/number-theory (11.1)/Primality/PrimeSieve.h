/**
 * Description: tests primality up to $SZ$
 * Time: O(SZ\log\log SZ)
 * Source: KACTL 
 * Verification: https://open.kattis.com/problems/primesieve
 */

template<int SZ> struct Sieve { 
	bitset<SZ> prime;
	vi pr;
	Sieve() {
		prime.set(); prime[0] = prime[1] = 0;
		for (int i = 4; i < SZ; i += 2) prime[i] = 0;
		for (int i = 3; i*i < SZ; i += 2) if (prime[i])
			for (int j = i*i; j < SZ; j += i*2) prime[j] = 0;
		F0R(i,SZ) if (prime[i]) pr.pb(i);
	}
};