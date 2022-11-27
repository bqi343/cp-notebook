/**
 * Description: Kirchhoff's Matrix Tree Theorem.
	* Given adjacency matrix, calculates \# of spanning trees.
 * Source: various
 * Verification: TC Finals 2022 1000
 */

#include "MatrixInv.h"

T numSpan(const Mat& m) { 
	int n = sz(m); Mat res = makeMat(n-1,n-1);
	F0R(i,n) FOR(j,i+1,n) {
		mi ed = m[i][j]; res[i][i] += ed;
		if (j != n-1) {
			res[j][j] += ed;
			res[i][j] -= ed, res[j][i] -= ed;
		}
	}
	return gauss(res).f;
}