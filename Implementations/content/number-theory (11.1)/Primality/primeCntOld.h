/**
 * Description: Counts number of primes up to $N$. Can also count 
 	* sum of primes. For faster performance, only consider odd values
 	* of \texttt{i} in the loops involving \texttt{B[i]}.
 * Time: $O(N^{3/4}/\log N)$, works for $N=10^{11}$.
 * Source: https://www.topcoder.com/single-round-match-741-editorials/
 	* also see faster https://codeforces.com/group/ZFgXbZSjvp/contest/274852/submission/76443529
 	* https://blog.csdn.net/bestFy/article/details/80100244
 * Verification: 
 	* https://codeforces.com/group/ZFgXbZSjvp/contest/274852/problem/A
 	* https://www.spoj.com/problems/DIVCNT3/
 */

#include "Sieve.h"

ll N; vl A, B; // sieve should store primes up to sqrt(N) and one more
ll primeCnt() { // A[i] stores # primes <= i
	int SN = sqrt(N);  A = B = vl(SN+1);
	FOR(i,1,SN+1) A[i] = i-1, B[i] = N/i-1;
	vd in(SN+1); FOR(i,1,SN+1) in[i] = 1.0/i;
	each(p,S.pr) { if (p > N/p) break;
		int np=A[p-1],mx=SN/p+1,r=min(N/p/p,(ll)SN);db tmp=N/p;
		FOR(i,1,mx) B[i]-=B[i*p]-np;
		FOR(i,mx,r+1) B[i]-=A[tmp*in[i]+1e-9]-np;
		ROF(i,p,mx) for(;r>=i*p;--r) A[r]-=A[i]-np;
	} // B[i] stores # primes <= N/i
	return B[1]; 
}
ll priNum(ll x) { return x < sz(A) ? A[x] : B[N/x]; }
ll pre(ll n, int ind) { // sum_{i=1}^n(# divisors of i^3)
	// only consider #s with prime divisors >= p
	ll p = S.pr[ind]; if (n < p) return 1;
	if (p*p > n) return 1+4*(priNum(n)-ind);
	ll res = pre(n,ind+1);
	for (int j=1;;++j) {
		n /= p; if (!n) break;
		res += (3*j+1)*pre(n,ind+1);
	}
	return res;
}
