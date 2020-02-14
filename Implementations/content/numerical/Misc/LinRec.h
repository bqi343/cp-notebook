/**
 * Description: Berlekamp-Massey, computes linear recurrence of 
 * order $N$ for sequence of $2N$ terms
 * Time: O(N^2)
 * Source: 
	* https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm
	* http://codeforces.com/blog/entry/61306
	* MIT ICPC notebook
 * Verification: http://codeforces.com/contest/506/problem/E
 */

#include "../Polynomials/Poly.h"
#include "../../number-theory (11.1)/Modular Arithmetic/ModInt.h"

struct LinRec {
	vmi x, C, rC;
	void init(const vmi& _x) { // original sequence
		x = _x; int n = sz(x), m = 0;
		vmi B; B = C = {1}; // B is fail vector
		mi b = 1; // B gives 0,0,0,...,b
		F0R(i,n) {
			m ++;
			mi d = x[i]; FOR(j,1,sz(C)) d += C[j]*x[i-j];
			if (d == 0) continue; // rec still works
			auto _B = C; C.rsz(max(sz(C),m+sz(B)));
			// subtract rec that gives 0,0,0,...,d
			mi coef = d/b; FOR(j,m,m+sz(B)) C[j] -= coef*B[j-m]; 
			if (sz(_B) < m+sz(B)) { B = _B; b = d; m = 0; }
		}
		rC = C; reverse(all(rC)); // poly for getPo
		C.erase(begin(C)); trav(t,C) t *= -1; 
		// x[i]=sum_{j=0}^{sz(C)-1}C[j]*x[i-j-1]
	}
	vmi getPo(int n) {
		if (n == 0) return {1};
		vmi x = getPo(n/2); x = rem(x*x,rC);
		if (n&1) { vmi v = {0,1}; x = rem(x*v,rC); }
		return x;
	}
	mi eval(int n) { // evaluate n-th term
		vmi t = getPo(n);
		mi ans = 0; F0R(i,sz(t)) ans += t[i]*x[i];
		return ans;
	}
};
