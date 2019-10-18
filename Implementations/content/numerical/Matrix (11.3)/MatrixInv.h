/**
 * Description: calculates determinant via gaussian elimination
 * Time: O(N^3)
 * Source: various
 * Verification: SPOJ MIFF (matrix inverse modulo prime)
 */

#include "Matrix.h"

template<class T> T gauss(Mat<T>& m) { // determinant of 1000x1000 Matrix in ~1s
	int n = m.r;
	T prod = 1; int nex = 0;
	F0R(i,n) {
		int row = -1; // for ld use EPS rather than 0
		FOR(j,nex,n) if (m.d[j][i] != 0) { row = j; break; } 
		if (row == -1) { prod = 0; continue; }
		if (row != nex) prod *= -1, swap(m.d[row],m.d[nex]);
		prod *= m.d[nex][i];
		auto x = 1/m.d[nex][i]; FOR(k,i,m.c) m.d[nex][k] *= x;
		F0R(j,n) if (j != nex) {
			auto v = m.d[j][i];
			if (v != 0) FOR(k,i,m.c) m.d[j][k] -= v*m.d[nex][k];
		}
		nex ++;
	}
	return prod;
}

template<class T> Mat<T> inv(Mat<T> m) {
	int n = m.r;
	Mat<T> x(n,2*n); 
	F0R(i,n) {
		x.d[i][i+n] = 1;
		F0R(j,n) x.d[i][j] = m.d[i][j];
	}
	if (gauss(x) == 0) return Mat<T>(0,0);
	Mat<T> r(n,n); 
	F0R(i,n) F0R(j,n) r.d[i][j] = x.d[i][j+n];
	return r;
}