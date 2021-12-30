/**
 * Description: Matching for general graphs. Fails with probability $N/MOD$.
 * Time: O(N^3)
 * Source: Simon Lindholm, KACTL
 	* http://www.mimuw.edu.pl/~mucha/pub/mucha_sankowski_focs04.pdf
 * Verification: https://codeforces.com/contest/1089/problem/B
 */

#include "MatrixInv.h"

vpi match(int N, vpi& ed) {
	Mat<mi> mat(N,N); // skew symmetric adj matrix
	each(pa, ed) {
		int a = pa.f, b = pa.s, r = rand() % MOD;
		mat.d[a][b] = r, mat.d[b][a] = (MOD-r) % MOD;
	}
	auto MAT = mat; int r = gauss(MAT).s, M = 2*N-r;
	assert(r%2 == 0); // rank <= 2*(size of matching)
	mat.r = mat.c = M; mat.d.rsz(M,vmi(M));
	F0R(i,N) mat.d[i].rsz(M);
	Mat<mi> A(0,0);
	while (A.r == 0) { // extend to make perfect matching
		F0R(i,N) FOR(j,N,M) {
			int r = rand() % MOD;
			mat.d[i][j] = r, mat.d[j][i] = -r;
		}
		A = inv(mat);
	}
	vi has(M,1); vpi ret;
	F0R(it,M/2) {
		int fi, fj;
		F0R(i,M) if (has[i])
			FOR(j,i+1,M) if (A.d[i][j] != 0 && mat.d[i][j] != 0) {
				fi = i; fj = j; goto done; // added edge
		} assert(0); done: // now remove corresponding rows / cols
		has[fi] = has[fj] = 0; if (fj < N) ret.eb(fi, fj);
		F0R(sw,2) { // calculate inverse for reduced adj matrix
			mi a = 1/A.d[fi][fj]; 
			F0R(i,M) if (has[i] && A.d[i][fj] != 0) {
				mi b = A.d[i][fj]*a;
				F0R(j,M) A.d[i][j] -= A.d[fi][j]*b;
			}
			swap(fi,fj);
		}
	}
	return ret;
}
