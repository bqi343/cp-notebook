/**
 * Description: Modified Chirp-Z. For $x\neq 0$, computes 
 	* $A(x^0), A(x^1), \ldots, A(x^{n-1})$.
 * Time: FFT(2|A|+n)
 * Source: https://cp-algorithms.com/algebra/polynomial.html
 	* https://github.com/e-maxx-eng/e-maxx-eng-aux/blob/master/src/polynomial.cpp
 	* https://codeforces.com/blog/entry/82165
 * Verification:
 	* https://codeforces.com/contest/1054/problem/H
 */

#include "FFT.h"

poly chirpz(poly A, T x, int n) {
	auto gen = [&](T c) -> poly {
		poly p(sz(A)+n); p[0] = 1;
		T t = 1; FOR(i,1,sz(p)) p[i] = p[i-1]*t, t *= c; 
		return p;
	}; // uses ij = -C(i,2)+C(i+j,2)-C(j,2)
	poly ip = gen(1/x); F0R(i,sz(A)) A[i] *= ip[i];
	reverse(all(A)); poly res = mul(A,gen(x)); 
	res = poly(sz(A)-1+all(res)); F0R(i,n) res[i] *= ip[i];
	return res;
}
// poly chirpzNaive(poly A, T x, int n) {
// 	poly res; F0R(i,n) res.pb(eval(A,pow(x,i)));
// 	return res; }