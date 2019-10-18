/**
 * Description: Simplex algorithm for linear programming,
	* maximize $c^Tx$ subject to $Ax \le b, x \ge 0$
 * Time: ?
 * Source: KACTL, Stanford
	* https://cs.stanford.edu/group/acm/SLPC/notebook.pdf
	* https://www.utdallas.edu/~scniu/OPRE-6201/documents/LP06-Simplex-Tableau.pdf
	* http://www.columbia.edu/~cs2035/courses/ieor3608.F05/bigm1.pdf
 * Verification:
	* https://open.kattis.com/contests/fvfhq4/problems/goatropes
	* http://codeforces.com/contest/375/problem/E
	* USACO Training cowwars
 */
 
typedef double T;
typedef vector<T> vd;
typedef vector<vd> vvd;
const T eps = 1e-8, inf = 1/.0;

#define ltj(X) if (s == -1 || mp(X[j],N[j]) < mp(X[s],N[s])) s=j

struct LPSolver {
	int m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
			F0R(i,m) F0R(j,n) D[i][j] = A[i][j];
			F0R(i,m) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i]; } // B[i] -> basic variables, col n+1 is for constants, why D[i][n]=-1?
			F0R(j,n) { N[j] = j; D[m][j] = -c[j]; } // N[j] -> non-basic variables, all zero
			N[n] = -1; D[m+1][n] = 1;
		}

	void print() {
		ps("D");
		trav(t,D) ps(t);
		ps();
		ps("B",B); 
		ps("N",N);
		ps();
	}
	
	void pivot(int r, int s) { // row, column
		T *a = D[r].data(), inv = 1/a[s]; // eliminate col s from consideration
		F0R(i,m+2) if (i != r && abs(D[i][s]) > eps) {
			T *b = D[i].data(), inv2 = b[s]*inv;
			F0R(j,n+2) b[j] -= a[j]*inv2;
			b[s] = a[s]*inv2;
		}
		F0R(j,n+2) if (j != s) D[r][j] *= inv;
		F0R(i,m+2) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv; swap(B[r], N[s]); // swap a basic and non-basic variable
	}

	bool simplex(int phase) {
		int x = m+phase-1;
		for (;;) {
			int s = -1; F0R(j,n+1) if (N[j] != -phase) ltj(D[x]); // find most negative col
			if (D[x][s] >= -eps) return true; // have best solution
			int r = -1;
			F0R(i,m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || mp(D[i][n+1] / D[i][s], B[i])
							 < mp(D[r][n+1] / D[r][s], B[r])) r = i; // find smallest positive ratio
			}
			if (r == -1) return false; // unbounded
			pivot(r, s);
		}
	}

	T solve(vd &x) {
		int r = 0; FOR(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) { // x=0 is not a solution
			pivot(r, n); // -1 is artificial variable, initially set to smth large but want to get to 0 
			if (!simplex(2) || D[m+1][n+1] < -eps) return -inf; // no solution
			// D[m+1][n+1] is max possible value of the negation of artificial variable, starts negative but should get to zero
			F0R(i,m) if (B[i] == -1) {
				int s = 0; FOR(j,1,n+1) ltj(D[i]);
				pivot(i,s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		F0R(i,m) if (B[i] < n) x[B[i]] = D[i][n+1];
		return ok ? D[m][n+1] : inf;
	}
};
