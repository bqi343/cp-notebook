/**
 * Description: Generalized Euclidean algorithm. \texttt{euclid} and 
 	* \texttt{invGeneral} work for $A,B<2^{62}$. 
 * Source: KACTL
 * Time: O(\log AB)
 * Verification: https://codeforces.com/gym/102411/problem/G
 */

// ceil(a/b)
// ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); }
pl euclid(ll A, ll B) { // For A,B>=0, finds (x,y) s.t.
	// Ax+By=gcd(A,B), |Ax|,|By|<=AB/gcd(A,B)
	if (!B) return {1,0};
	pl p = euclid(B,A%B); return {p.s,p.f-A/B*p.s}; }
ll invGeneral(ll A, ll B) { // find x in [0,B) such that Ax=1 mod B
	pl p = euclid(A,B); assert(p.f*A+p.s*B == 1);
	return p.f+(p.f<0)*B; } // must have gcd(A,B)=1