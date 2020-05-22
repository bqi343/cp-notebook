/**
 * Description: Compute $A(x^0), A(x^1), A(x^{n-1})$ for any polynomial $A$.
 * Time: $(|A|+n)\log (|A|+n)$
 * Source: https://cp-algorithms.com/algebra/polynomial.html
 	* https://github.com/e-maxx-eng/e-maxx-eng-aux/blob/master/src/polynomial.cpp
 */

#include "PolyConv.h"

poly chirpzEven(poly A, T x, int n) { // A(1), A(x^2), ..., A(x^{2(n-1)})
	poly p(max(sz(A),n)); T tmp = 1;
	F0R(i,sz(p)) {
		if (i == 0) p[i] = 1;
		else p[i] = p[i-1]*x*tmp, tmp *= x*x;
	}
	F0R(i,sz(A)) A[i] *= p[i];
	int lo = sz(A)-1; 
	poly dif; FOR(i,-lo,n) dif.pb(T{1}/p[abs(i)]);
	poly res = conv(A,dif);
	poly ans; F0R(i,n) ans.pb(res[i+lo]*p[i]);
	return ans;
}
poly chirpz(poly A, T x, int n) {
	poly even = chirpzEven(A,x,(n+1)/2);
	F0R(i,sz(A)) A[i] *= pow(x,i);
	poly odd = chirpzEven(A,x,n/2);
	poly res(n); F0R(i,n) res[i] = (i&1?odd[i/2]:even[i/2]);
	return res; 
}
// poly chirpzNaive(poly A, T x, int n) {
// 	poly res; F0R(i,n) res.pb(eval(A,pow(x,i)));
// 	return res; }