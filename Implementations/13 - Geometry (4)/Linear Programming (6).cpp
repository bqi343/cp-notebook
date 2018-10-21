/**
 * Description: Simplex Algorithm for linear programming
    * maximize cˆT x subject to Ax <= b, x >= 0; (oops I should try to understand all the code)
 * Usage: 
 	* https://open.kattis.com/contests/fvfhq4/problems/goatropes
 	* http://codeforces.com/contest/375/problem/E
 * Source: KACTL, Stanford
 */
 
typedef double T;
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = 1/.0;
#define ltj(X) if(s == -1 || mp(X[j],N[j]) < mp(X[s],N[s])) s=j

struct LPSolver {
	int m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
			F0R(i,m) F0R(j,n) D[i][j] = A[i][j];
			F0R(i,m) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i];}
			F0R(j,n) { N[j] = j; D[m][j] = -c[j]; }
			N[n] = -1; D[m+1][n] = 1;
		}

	void pivot(int r, int s) { // row, column
		T *a = D[r].data(), inv = 1 / a[s]; // eliminate col s from consideration?
		F0R(i,m+2) if (i != r && abs(D[i][s]) > eps) {
			T *b = D[i].data(), inv2 = b[s] * inv;
			F0R(j,n+2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		F0R(j,n+2) if (j != s) D[r][j] *= inv;
		F0R(i,m+2) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = m + phase - 1;
		for (;;) {
			int s = -1;
			F0R(j,n+1) if (N[j] != -phase) ltj(D[x]); // find most negative col
			if (D[x][s] >= -eps) return true;
			int r = -1;
		    F0R(i,m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || mp(D[i][n+1] / D[i][s], B[i])
				             < mp(D[r][n+1] / D[r][s], B[r])) r = i; // find smallest positive ratio
			}
			if (r == -1) return false;
			pivot(r, s); 
		}
	}

	T solve(vd &x) {
		int r = 0;
    		FOR(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) {
			pivot(r, n);
			if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
			F0R(i,m) if (B[i] == -1) {
				int s = 0;
				FOR(j,1,n+1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		F0R(i,m) if (B[i] < n) x[B[i]] = D[i][n+1];
		return ok ? D[m][n+1] : inf;
	}
};

/*vvd A; vd B,C;
int co = 0; // # extra variables

void addIneq(vd a, double b) { // a*x <= b
    F0R(i,co) a.pb(0);
    a.pb(1); co ++;
    for (auto& z: A) z.pb(0);
    A.pb(a); B.pb(b); C.pb(0);
}*/
