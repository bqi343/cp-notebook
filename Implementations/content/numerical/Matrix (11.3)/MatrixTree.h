/**
 * Description: Kirchhoff's Matrix Tree Theorem.
	* Given adjacency matrix, calculates \# of spanning trees.
 * Source: various
 * Verification: SPOJ MIFF (matrix inverse modulo prime)
 */

#include "MatrixInv.h"

T numSpan(Mat m) { 
	int n = sz(m); Mat res(n-1,n-1);
	F0R(i,n) FOR(j,i+1,n) {
		mi ed = m[i][j]; res[i][i] += ed;
		if (j != n-1) {
			res[j][j] += ed;
			res[i][j] -= ed, res[j][i] -= ed;
		}
	}
	return gauss(res).f;
}