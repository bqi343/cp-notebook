/**
 * Description: ?
 * Source: KACTL
 * Verification: https://codeforces.com/contest/1007/problem/D
 */

#include "SCC.h"

template<int SZ> struct TwoSat {
	SCC<2*SZ> S;
	bitset<SZ> ans;
	int N = 0;
	int addVar() { return N++; }

	void either(int x, int y) { 
		x = max(2*x,-1-2*x), y = max(2*y,-1-2*y);
		S.addEdge(x^1,y); S.addEdge(y^1,x); 
	}
	void implies(int x, int y) { either(~x,y); }
	void setVal(int x) { either(x,x); }
	void atMostOne(const vi& li) {
		if (sz(li) <= 1) return;
		int cur = ~li[0];
		FOR(i,2,sz(li)) {
			int next = addVar();
			either(cur,~li[i]);
			either(cur,next);
			either(~li[i],next);
			cur = ~next;
		}
		either(cur,~li[1]);
	}

	bool solve(int _N) {
		if (_N != -1) N = _N; 
		S.init(2*N);
		for (int i = 0; i < 2*N; i += 2) 
			if (S.comp[i] == S.comp[i^1]) return 0;
		reverse(all(S.allComp));
		vi tmp(2*N);
		trav(i,S.allComp) if (tmp[i] == 0) 
			tmp[i] = 1, tmp[S.comp[i^1]] = -1;
		F0R(i,N) if (tmp[S.comp[2*i]] == 1) ans[i] = 1;
		return 1;
	}
};