/**
 * Description: Uses gaussian elimination to convert into reduced row echelon form
	* and calculates determinant. For determinant via arbitrary modulos, 
	* use a modified form of the Euclidean algorithm because modular inverse 
	* may not exist. If you have computed $A^{-1}\pmod{p^k},$ then the inverse 
	* $\pmod{p^{2k}}$ is $A^{-1}(2I-AA^{-1}).$
 * Time: O(N^3), determinant of $1000\times 1000$ matrix of modints in 
	* 1 second if you reduce \# of operations by half
 * Source: various
 * Verification: 
	* SPOJ MIFF (matrix inverse modulo prime)
	* https://open.kattis.com/problems/equationsolver
 */

#include "Matrix.h"

const ld EPS = 1e-12;
int getRow(Mat<ld>& m, int n, int i, int nex) {
	pair<ld,int> bes = {0,-1};
	FOR(j,nex,n) ckmax(bes,{abs(m.d[j][i]),j}); 
	return bes.f < EPS ? -1 : bes.s;
}
int getRow(Mat<mi>& m, int n, int i, int nex) {
	FOR(j,nex,n) if (m.d[j][i] != 0) return j;
	return -1;
}
template<class T> pair<T,int> gauss(Mat<T>& m) { 
	int n = m.r, rank = 0, nex = 0;
	T prod = 1; // determinant
	F0R(i,n) {
		int row = getRow(m,n,i,nex);
		if (row == -1) { prod = 0; continue; }
		if (row != nex) prod *= -1, swap(m.d[row],m.d[nex]);
		prod *= m.d[nex][i]; rank ++;
		auto x = 1/m.d[nex][i]; FOR(k,i,m.c) m.d[nex][k] *= x;
		F0R(j,n) if (j != nex) {
			auto v = m.d[j][i]; if (v == 0) continue;
			FOR(k,i,m.c) m.d[j][k] -= v*m.d[nex][k];
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