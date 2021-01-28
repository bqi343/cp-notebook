/**
 * Description: Counts number of primes up to $n$. Can also count sum of primes.
 * Time: $O(n^{3/4}/\log n)$
 * Source: neal
 * Verification: https://codeforces.com/group/ZFgXbZSjvp/contest/274852/problem/A
 */

template<int SZ> struct Sieve { 
	bitset<SZ> pri; vi pr, cum; 
	Sieve() { // cum[i] = # of primes up to i
		pri.set(); pri[0] = pri[1] = 0;
		for (int i = 4; i < SZ; i += 2) pri[i] = 0;
		for (int i = 3; i*i < SZ; i += 2) if (pri[i])
			for (int j = i*i; j < SZ; j += i*2) pri[j] = 0;
		F0R(i,SZ) {
			cum.pb(i?cum.bk:0);
			if (pri[i]) pr.pb(i), cum.bk ++;
		}
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

template<int SZ> struct PrimeCnt { 
	Sieve<SZ> S; // SZ=1e7 is fine for N<=10^{11}
	static const int N = 1e5, K = 50; 
	uint16_t memo[N][K]; // use 32-bit if N >= 2^17
	PrimeCnt() { memset(memo,0,sizeof memo); }
	ll countNo(ll n, int k) { // # of #s in [1,n] not divisible
		if (k == 0) return n; // by any of first k primes
		ll p = S.pr[k]; if (n < p) return 1;
		if (n < min((ll)SZ,p*p)) return S.cum[n]-k+1;
		bool save = n < N && k < K;
		if (save && memo[n][k]) return memo[n][k];
		p = S.pr[k-1]; ll ret = countNo(n,k-1)-countNo(n/p,k-1);
		if (save) memo[n][k] = ret;
		return ret;
	} // for k<X^{1/4}: <= X^{1/2} values of n
	// for X^{1/4}<k<=X^{1/2}: <= X^{1/2}/k values of n>X^{1/2}
	ll get(ll X) { // k ~ sqrt(n)/logn
		if (X < SZ) return S.cum[X];
		int k = S.cum[sqrt(X)]; return countNo(X,k)+k-1;
	}
};
