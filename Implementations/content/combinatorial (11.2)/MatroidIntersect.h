/**
 * Description: computes a set of maximum size which is independent 
 	* in both graphic and colorful matroids, aka a spanning forest where
 	* no two edges are of the same color
 * Time: $O(GI^{1.5})$ calls to oracles, where $G$ is the size of the ground set 
 	* and $I$ is the size of the independent set
 * Source: https://codeforces.com/blog/entry/69287
 * Verification: https://www.spoj.com/problems/COIN/
 */

#include "DSU.h"

int R;
map<int,int> m;
 
struct Element {
	pi ed;
	int col;
	bool in_independent_set = 0;
	int independent_set_position;
	Element(int u, int v, int c) { ed = {u,v}; col = c; }
};
 
vi independent_set;
vector<Element> ground_set;
bool col_used[300];

struct GBasis {
	DSU D;
	void reset() { D.init(sz(m)); } 
	void add(pi v) { assert(D.unite(v.f,v.s)); }
	bool independent_with(pi v) { return !D.sameSet(v.f,v.s); }
};
 
GBasis basis, basis_wo[300];
 
bool graph_oracle(int inserted) {
	return basis.independent_with(ground_set[inserted].ed);
}
bool graph_oracle(int inserted, int removed) {
	int wi = ground_set[removed].independent_set_position;
	return basis_wo[wi].independent_with(ground_set[inserted].ed);
}
void prepare_graph_oracle() {
	basis.reset();
	F0R(i,sz(independent_set)) basis_wo[i].reset();
	F0R(i,sz(independent_set)) {
		pi v = ground_set[independent_set[i]].ed; basis.add(v);
		F0R(j,sz(independent_set)) if (i != j) basis_wo[j].add(v);
	}
}
 
bool colorful_oracle(int ins) {
	ins = ground_set[ins].col;
	return !col_used[ins];
}
bool colorful_oracle(int ins, int rem) {
	ins = ground_set[ins].col;
	rem = ground_set[rem].col;
	return !col_used[ins] || ins == rem;
}
void prepare_colorful_oracle() {
	F0R(i,R) col_used[i] = 0;
	trav(t,independent_set) col_used[ground_set[t].col] = 1;
}
 
bool augment() {
	prepare_graph_oracle();
	prepare_colorful_oracle();
	
	vi par(sz(ground_set),MOD);
	queue<int> q;
	F0R(i,sz(ground_set)) if (colorful_oracle(i)) {
		assert(!ground_set[i].in_independent_set);
		par[i] = -1; q.push(i);
	}
	int lst = -1;
	while (sz(q)) {
		int cur = q.front(); q.pop();
		if (ground_set[cur].in_independent_set) {
			F0R(to,sz(ground_set)) if (par[to] == MOD) {
				if (!colorful_oracle(to,cur)) continue;
				par[to] = cur; q.push(to);
			}
		} else {
			if (graph_oracle(cur)) { lst = cur; break;	}
			trav(to,independent_set) if (par[to] == MOD) {
				if (!graph_oracle(cur,to)) continue;
				par[to] = cur; q.push(to);
			}
		}
	}
	if (lst == -1) return 0;
	do {
		ground_set[lst].in_independent_set ^= 1;
		lst = par[lst];
	} while (lst != -1);
	independent_set.clear();
	F0R(i,sz(ground_set)) if (ground_set[i].in_independent_set) {
		ground_set[i].independent_set_position = sz(independent_set);
		independent_set.pb(i);
	}
	return 1;
}
 
void solve() {
	re(R); if (R == 0) exit(0);
	m.clear(); ground_set.clear(); independent_set.clear();
	F0R(i,R) {
		int a,b,c,d; re(a,b,c,d);
		ground_set.pb(Element(a,b,i));
		ground_set.pb(Element(c,d,i));
		m[a] = m[b] = m[c] = m[d] = 0;
	}
	int co = 0;
	trav(t,m) t.s = co++;
	trav(t,ground_set) t.ed.f = m[t.ed.f], t.ed.s = m[t.ed.s];
	while (augment());
	ps(2*sz(independent_set));
}