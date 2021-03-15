/**
 * Description: computes $A^{-1}$ such that $AA^{-1}\equiv 1\pmod{x^n}$.
 	* Newton's method: If you want $F(x)=0$ and $F(Q_k)\equiv 0\pmod{x^a}$
 	* then $Q_{k+1}=Q_k-\frac{F(Q_k)}{F'(Q_k)}\pmod{x^{2a}}$ satisfies
 	* $F(Q_{k+1})\equiv 0 \pmod{x^{2a}}$. Application: if $f(n),g(n)$ are the
 	* \#s of forests and trees on $n$ nodes then 
 	* $\sum_{n=0}^{\infty}f(n)x^n=\exp\left(\sum_{n=1}^{\infty}\frac{g(n)}{n!}\right)$.
 * Time: O(N\log N)
 * Source: CF, http://people.csail.mit.edu/madhu/ST12/scribe/lect06.pdf
 	* https://cp-algorithms.com/algebra/polynomial.html
 * Usage: vmi v={1,5,2,3,4}; ps(exp(2*log(v,9),9)); // squares v
 * Verification: https://codeforces.com/contest/438/problem/E
 	* https://codeforces.com/gym/102028/submission/77687049
 	* https://loj.ac/problem/6703 (MultipointEval)
 */

#include "PolyConv.h"

poly inv(poly A, int n) { // Q-(1/Q-A)/(-Q^{-2})
	poly B{1/A[0]};
	for (int x = 2; x/2 < n; x *= 2)
		B = 2*B-RSZ(conv(RSZ(A,x),conv(B,B)),x);
	return RSZ(B,n);
}
poly sqrt(const poly& A, int n) {  // Q-(Q^2-A)/(2Q)
	assert(A[0] == 1); poly B{1};
	for (int x = 2; x/2 < n; x *= 2)
		B = T(1)/T(2)*RSZ(B+conv(RSZ(A,x),inv(B,x)),x);
	return RSZ(B,n);
}
pair<poly,poly> divi(const poly& f, const poly& g) { // return quotient and remainder
	if (sz(f) < sz(g)) return {{},f};
	poly q = conv(inv(rev(g),sz(f)-sz(g)+1),rev(f));
	q = rev(RSZ(q,sz(f)-sz(g)+1));
	poly r = RSZ(f-conv(q,g),sz(g)-1); return {q,r};
}
poly log(poly A, int n) { assert(A[0] == 1); // (ln A)' = A'/A
	A.rsz(n); return integ(RSZ(conv(dif(A),inv(A,n-1)),n-1)); }
poly exp(poly A, int n) { assert(A[0] == 0);
	poly B{1}, IB{1};
	for (int x = 1; x < n; x *= 2) {
		IB = 2*IB-RSZ(conv(B,conv(IB,IB)),x); // inverse of B to x places
		poly Q = dif(RSZ(A,x)); Q += RSZ(conv(IB,dif(B)-conv(B,Q)),2*x-1); 
		// first x-1 terms of dif(B)-conv(B,Q) are zero
		B = B+RSZ(conv(B,RSZ(A,2*x)-integ(Q)),2*x); 
	} // We know that Q=A' is B'/B to x-1 places, we want to find B'/B to 2x-1 places
	return RSZ(B,n);
}
// poly expOld(poly A, int n) { // Q-(lnQ-A)/(1/Q)
// 	assert(A[0] == 0); poly B = {1};
// 	while (sz(B) < n) { int x = 2*sz(B);
// 		B = RSZ(B+conv(B,RSZ(A,x)-log(B,x)),x); }
// 	return RSZ(B,n);
// }