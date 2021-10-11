/**
 * Description: Solves a general linear maximization problem: 
 	* maximize $c^T x$ subject to $Ax \le b$, $x \ge 0$.
	* Returns \texttt{-inf} if there is no solution, 
	* \texttt{inf} if there are arbitrarily good solutions, 
	* or the maximum value of $c^T x$ otherwise.
	* The input vector is set to an optimal $x$ 
	* (or in the unbounded case, an arbitrary solution fulfilling the constraints).
	* Numerical stability is not guaranteed. For better performance, 
	* define variables such that $x = 0$ is viable.
 * Usage:
	 * vvd A{{1,-1}, {-1,1}, {-1,-2}};
	 * vd b{1,1,-4}, c{-1,-1}, x;
	 * T val = LPSolver(A, b, c).solve(x);
 * Time: O(NM \cdot \#pivots), where a pivot may be e.g. an edge relaxation. O(2^N) in the general case.
 * Source: KACTL, Stanford
	* https://cs.stanford.edu/group/acm/SLPC/notebook.pdf
	* https://www.utdallas.edu/~scniu/OPRE-6201/documents/LP06-Simplex-Tableau.pdf (good example)
	* http://www.columbia.edu/~cs2035/courses/ieor3608.F05/bigm1.pdf
	* https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-design-and-analysis-of-algorithms-spring-2015/lecture-notes/MIT6_046JS15_lec15.pdf
 * Verification: 
    * https://open.kattis.com/contests/ecna19open/problems/cheeseifyouplease
    * https://codeforces.com/gym/101242 (Road Times) 
 */
 
using T = db; // double probably suffices
using vd = V<T>; using vvd = V<vd>;
const T eps = 1e-8, inf = 1/.0;

#define ltj(X) if (s==-1 || mp(X[j],N[j])<mp(X[s],N[s])) s=j
struct LPSolver {
	int m, n; // # m = contraints, # n = variables
	vi N, B; // N[j] = non-basic variable (j-th column), = 0
	vvd D; // B[j] = basic variable (j-th row)
	LPSolver(const vvd& A, const vd& b, const vd& c) :
	  m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
		F0R(i,m) F0R(j,n) D[i][j] = A[i][j]; 
		F0R(i,m) B[i] = n+i, D[i][n] = -1, D[i][n+1] = b[i];
		// B[i]: basic variable for each constraint
		// D[i][n]: artificial variable for testing feasibility
		F0R(j,n) N[j] = j, D[m][j] = -c[j];
		// D[m] stores negation of objective, 
		// which we want to minimize
		N[n] = -1; D[m+1][n] = 1; // to find initial feasible
	} // solution, minimize artificial variable
	void pivot(int r, int s) { // swap B[r] (row)
		T inv = 1/D[r][s]; // with N[r] (column)
		F0R(i,m+2) if (i != r && abs(D[i][s]) > eps) {
			T binv = D[i][s]*inv;
			F0R(j,n+2) if (j != s) D[i][j] -= D[r][j]*binv;
			D[i][s] = -binv;
		}
		D[r][s] = 1; F0R(j,n+2) D[r][j] *= inv; // scale r-th row
		swap(B[r],N[s]);
	}
	bool simplex(int phase) {
		int x = m+phase-1;
		while (1) { // if phase=1, ignore artificial variable
			int s = -1; F0R(j,n+1) if (N[j] != -phase) ltj(D[x]); 
			// find most negative col for nonbasic (NB) variable
			if (D[x][s] >= -eps) return 1; 
			// can't get better sol by increasing NB variable
			int r = -1;
			F0R(i,m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || mp(D[i][n+1] / D[i][s], B[i])
							 < mp(D[r][n+1] / D[r][s], B[r])) r = i; 
				// find smallest positive ratio
			} // -> max increase in NB variable
			if (r == -1) return 0; // objective is unbounded
			pivot(r,s);
		}
	}
	T solve(vd& x) { // 1. check if x=0 feasible
		int r = 0; FOR(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) { // if not, find feasible start
			pivot(r,n); // make artificial variable basic
			assert(simplex(2)); // I think this will always be true??
			if (D[m+1][n+1] < -eps) return -inf;
			// D[m+1][n+1] is max possible value of the negation of 
			// artificial variable, optimal value should be zero 
			// if exists feasible solution
			F0R(i,m) if (B[i] == -1) { // artificial var basic
				int s = 0; FOR(j,1,n+1) ltj(D[i]); // -> nonbasic
				pivot(i,s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		F0R(i,m) if (B[i] < n) x[B[i]] = D[i][n+1];
		return ok ? D[m][n+1] : inf;
	}
};
