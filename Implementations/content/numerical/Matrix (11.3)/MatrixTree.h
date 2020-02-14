/**
 * Description: Kirchhoff's Matrix Tree Theorem.
	* Given adjacency matrix, calculates \# of spanning trees.
 * Source: various
 * Verification: SPOJ MIFF (matrix inverse modulo prime)
 */

#include "MatrixInv.h"
#include "../../number-theory (11.1)/Modular Arithmetic/ModInt.h"

mi numSpan(Mat<mi> m) { 
	int n = m.r; Mat<mi> res(n-1,n-1);
	F0R(i,n) FOR(j,i+1,n) {
		mi ed = m.d[i][j]; res.d[i][i] += ed;
		if (j != n-1) {
			res.d[j][j] += ed;
			res.d[i][j] -= ed, res.d[j][i] -= ed;
		}
	}
	return gauss(res).f;
}
