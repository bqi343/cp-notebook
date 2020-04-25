/**
 * Description: Berlekamp-Massey, computes linear recurrence of 
 * order $N$ for sequence of $2N$ terms
 * Time: If $R$ is reccurrence length, then \texttt{init} $\implies O(NR)$
 	* and \texttt{eval} $\implies O(R^2\log p)$.
 * Usage: LinRec L; L.init({0,1,1,2,3,5,8}); // Fibonacci
 * Source: 
	* https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm
	* http://codeforces.com/blog/entry/61306
	* MIT ICPC notebook
 * Verification: http://codeforces.com/contest/506/problem/E
 */

#include "../Polynomials/Poly.h"

struct LinRec {
	poly x, C, rC; 
	void init(const poly& _x) { // original sequence
		x = _x; int n = sz(x), m = 0; T b = 1; // B gives 0,0,...,b
		poly B; B = C = {1}; // B is fail vector
		F0R(i,n) {
			m ++; T d = x[i]; FOR(j,1,sz(C)) d += C[j]*x[i-j];
			if (d == 0) continue; // rec still works
			auto _B = C; C.rsz(max(sz(C),m+sz(B)));
			// subtract rec that gives 0,0,0,...,d
			T coef = d/b; FOR(j,m,m+sz(B)) C[j] -= coef*B[j-m]; 
			if (sz(_B) < m+sz(B)) B = _B, b = d, m = 0; 
		}
		rC = C; reverse(all(rC)); // poly for getPo
		C.erase(begin(C)); trav(t,C) t *= -1;
	} // x[i]=sum_{j=0}^{sz(C)-1}C[j]*x[i-j-1]
	poly getPo(ll p) { // get x^p mod rC
		if (p == 0) return {1};
		poly r = getPo(p/2); r = rem(r*r,rC);
		return p&1?rem(r*poly{0,1},rC):r;
	}
	T dot(poly v) { // dot product with seq
		T ans = 0; F0R(i,sz(v)) ans += v[i]*x[i];
		return ans; } // get p-th term of rec
	T eval(ll p) { assert(p >= 0); return dot(getPo(p)); } 
};