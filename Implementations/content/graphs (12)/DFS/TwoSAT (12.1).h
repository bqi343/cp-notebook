/**
 * Description: Calculates a valid assignment to boolean variables a, b, c,... 
 	* to a 2-SAT problem, so that an expression of the type 
 	* $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, 
 	* or reports that it is unsatisfiable.
 	* Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
	* TwoSat ts;
	* ts.either(0, \tilde3); // Var 0 is true or var 3 is false
	* ts.setVal(2); // Var 2 is true
	* ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
	* ts.solve(N); // Returns true iff it is solvable
	* ts.ans[0..N-1] holds the assigned values to the vars
 * Source: KACTL
 * Verification: https://codeforces.com/contest/1007/problem/D
 	* https://cses.fi/problemset/task/1684/
 */

#include "SCC (12.1).h"

struct TwoSAT {
	int N; SCC S; vector<bool> ans;
	void init(int _N) { N = _N; S.init(2*N); ans.rsz(N); }
	int addVar() { return N++; }
	void either(int x, int y) { 
		x = max(2*x,-1-2*x), y = max(2*y,-1-2*y);
		S.ae(x^1,y); S.ae(y^1,x); }
	void implies(int x, int y) { either(~x,y); }
	void must(int x) { either(x,x); }
	void atMostOne(vi li) {
		if (sz(li) <= 1) return;
		int cur = ~li[0];
		FOR(i,2,sz(li)) {
			int next = addVar();
			either(cur,~li[i]); either(cur,next);
			either(~li[i],next); cur = ~next;
		}
		either(cur,~li[1]);
	}
	bool solve(int _N = -1) {
		if (_N != -1) N = _N, S.init(2*N);
		S.gen(); reverse(all(S.comps)); // reverse topological order
		for (int i = 0; i < 2*N; i += 2) 
			if (S.comp[i] == S.comp[i^1]) return 0;
		vi tmp(2*N); each(i,S.comps) if (!tmp[i]) 
			tmp[i] = 1, tmp[S.comp[i^1]] = -1;
		F0R(i,N) if (tmp[S.comp[2*i]] == 1) ans[i] = 1;
		return 1;
	}
};
