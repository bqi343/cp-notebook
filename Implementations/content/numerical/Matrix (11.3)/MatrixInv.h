/**
 * Description: Calculates determinant via gaussian elimination. 
 	* For doubles use \texttt{abs(m.d[j][i]) > EPS} in place of \texttt{m.d[j][i] != 0}.
 	* For determinant via arbitrary modulos, use a modified form of the Euclidean
 	* algorithm because modular inverse may not exist.
 * Time: O(N^3), determinant of $1000\times 1000$ matrix of modular ints in 
 	* 1 second if you reduce \# of operations by half
 * Source: various
 * Verification: 
 	* SPOJ MIFF (matrix inverse modulo prime)
 	* https://open.kattis.com/problems/equationsolver
 */

#include "Matrix.h"

const ld EPS = 1e-8;
template<class T> pair<T,int> gauss(Mat<T>& m) { 
	int n = m.r, rank = 0, nex = 0;
	T prod = 1; 
	F0R(i,n) {
		int row = -1; 
		FOR(j,nex,n) if (m.d[j][i] != 0) { row = j; break; } 
		if (row == -1) { prod = 0; continue; }
		if (row != nex) prod *= -1, swap(m.d[row],m.d[nex]);
		prod *= m.d[nex][i]; rank ++;
		auto x = 1/m.d[nex][i]; FOR(k,i,m.c) m.d[nex][k] *= x;
		F0R(j,n) if (j != nex) {
			auto v = m.d[j][i];
			if (v != 0) FOR(k,i,m.c) m.d[j][k] -= v*m.d[nex][k];
		}
		nex ++;
	}
	return {prod,rank};
}
template<class T> Mat<T> inv(Mat<T> m) {
	assert(m.r == m.c);
	int n = m.r; Mat<T> x(n,2*n); 
	F0R(i,n) {
		x.d[i][i+n] = 1;
		F0R(j,n) x.d[i][j] = m.d[i][j];
	}
	if (gauss(x).s != n) return Mat<T>();
	Mat<T> res(n,n); 
	F0R(i,n) F0R(j,n) res.d[i][j] = x.d[i][j+n];
	return res;
}