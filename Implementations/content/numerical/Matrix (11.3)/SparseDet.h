/**
 * Description: Tries to find characteristic equation of matrix -> determinant.
 * Source: 
 	* https://github.com/yosupo06/library-checker-problems/blob/a14bd2360b01cac091efa8cc62cee0a9b65ae775/math/sparse_matrix_det/sol/correct.cpp
 	* https://mathworld.wolfram.com/CharacteristicEquation.html
 	* https://codeforces.com/blog/entry/76945?#comment-638126
 * Verification: https://judge.yosupo.jp/problem/sparse_matrix_det
 */

#include "LinRec.h"

mi sparseDet(int N, vector<pair<pi,mi>> A) { // nonzero entries of matrix, no repeats
	auto gen = []() { return rng()%(MOD-1)+1; };
	vmi l(N), r(N), seq(2*N); F0R(i,N) l[i] = gen(), r[i] = gen();
	F0R(i,2*N) { // consider l*A^i*r, recurrence satisfies characteristic equation
		F0R(j,N) seq[i] += l[j]*r[j];
		vmi R(N); each(t,A) R[t.f.s] += r[t.f.f]*t.s;
		swap(r,R);
	}
	LinRec L; L.init(seq); // hopefully found characteristic equation
	if (L.C.bk == 0) return 0; // 0 is root of characteristic equation
	if (sz(L.C) != N) return sparseDet(N,ed); // keep trying ...
	mi res = L.C.bk; if (!(N&1)) res *= -1; 
	return res;
};
