/**
 * Description: Characteristic polynomial of matrix.
 * Time: O(N^4), O(N^3)
 * Verification: K from https://official.contest.yandex.ru/opencupXX/contest/17333/enter/
 	* relevant paper: https://www.hindawi.com/journals/mpe/2014/750618/
 * Source:
 	* https://www.sciencedirect.com/science/article/pii/0895717793902662 (n^4)
 		* https://artofproblemsolving.com/wiki/index.php/Newton%27s_Sums
 	* http://www.cecm.sfu.ca/CAG/papers/CPpaper.pdf (n^3)
 */

#include "Matrix.h"
#include "Poly.h"

T tr(const Mat& m) { // trace
	int n = sz(m); assert(n == sz(m[0]));
	T ans = 0; F0R(i,n) ans += m[i][i];
	return ans; } // essentially newton sums
poly charPolySlow(Mat A) {
	poly c{1}; 
	int n = sz(A); Mat B = makeMat(n,n);
	FOR(i,1,n+1) B = A*B+A*c.bk, c.pb(-tr(B)/i);
	reverse(all(c)); return c;
}

Mat upperHB(Mat M) { // when k >= j+2, M[k][j] = 0
	int n = sz(M); // characteristic poly remains the same
	F0R(j,n-2) FOR(i,j+2,n) if (M[i][j] != 0) {
		if (M[j+1][j] == 0) {
			swap(M[i],M[j+1]);
			F0R(I,n) swap(M[I][i],M[I][j+1]);
		}
		mi in = 1/M[j+1][j];
		FOR(k,j+2,n) {
			mi u = M[k][j]*in;
			M[k] -= u*M[j+1]; // subtract multiple of j+1'th row from k-th
			F0R(I,n) M[I][j+1] += u*M[I][k]; // add multiple of k'th column to j+1-th
		}
		break;
	}
	return M;
}
poly charUpperHB(Mat M) {
	int n = sz(M);
	vector<poly> p(n+1); p[0] = {1};
	F0R(k,n) { // casework based on which entry you choose in column k
		p[k+1] = poly{-M[k][k],1}*p[k]; mi t = 1; // char poly for first (k+1) rows * (k+1) cols
		F0R(i,k) {
			t *= M[k-i][k-i-1];
			p[k+1] -= t*M[k-i-1][k]*p[k-i-1];
		}
	}
	return p[n];
}
poly charPoly(Mat M) { return charUpperHB(upperHB(M)); }