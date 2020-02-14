/**
 * Description: Computes a set of maximum size which is independent 
 	* in both graphic and colorful matroids, aka a spanning forest where
 	* no two edges are of the same color. In general, construct the exchange
 	* graph and find a shortest path.
 * Time: $O(GI^{1.5})$ calls to oracles, where $G$ is the size of the ground set 
 	* and $I$ is the size of the independent set
 * Source: https://codeforces.com/blog/entry/69287
 * Verification: https://www.spoj.com/problems/COIN/
 */

#include "../graphs (12)/DSU/DSU (7.6).h"

map<int,int> m;
struct Element {
	pi ed; int col;
	bool indep = 0; int ipos; // independent set pos
	Element(int u, int v, int c) { ed = {u,v}; col = c; }
};
vi iset; // independent set
vector<Element> gset; // ground set
struct GBasis {
	DSU D;
	void reset() { D.init(sz(m)); } 
	void add(pi v) { assert(D.unite(v.f,v.s)); }
	bool indep(pi v) { return !D.sameSet(v.f,v.s); }
};
GBasis basis;
vector<GBasis> basisWo; // basis without

bool graphOracle(int ins) { return basis.indep(gset[ins].ed); }
bool graphOracle(int ins, int rem) {
	return basisWo[gset[rem].ipos].indep(gset[ins].ed); }
void prepGraphOracle() {
	basis.reset(); F0R(i,sz(iset)) basisWo[i].reset();
	F0R(i,sz(iset)) {
		pi v = gset[iset[i]].ed; basis.add(v);
		F0R(j,sz(iset)) if (i != j) basisWo[j].add(v);
	}
}
vector<bool> colUsed;
bool colorOracle(int ins) { 
	ins = gset[ins].col; return !colUsed[ins]; }
bool colorOracle(int ins, int rem) {
	ins = gset[ins].col, rem = gset[rem].col;
	return !colUsed[ins] || ins == rem;
}
void prepColorOracle() {
	colUsed = vector<bool>(sz(colUsed),0);
	trav(t,iset) colUsed[gset[t].col] = 1;
}
 
bool augment() {
	prepGraphOracle(); prepColorOracle();
	vi par(sz(gset),MOD); queue<int> q;
	F0R(i,sz(gset)) if (!gset[i].indep && colorOracle(i)) 
		par[i] = -1, q.push(i);
	int lst = -1;
	while (sz(q)) {
		int cur = q.ft; q.pop();
		if (gset[cur].indep) {
			F0R(to,sz(gset)) if (!gset[to].indep && par[to] == MOD) {
				if (!colorOracle(to,cur)) continue;
				par[to] = cur; q.push(to);
			}
		} else {
			if (graphOracle(cur)) { lst = cur; break;	}
			trav(to,iset) if (par[to] == MOD) {
				if (!graphOracle(cur,to)) continue;
				par[to] = cur; q.push(to);
			}
		}
	}
	if (lst == -1) return 0;
	do {
		gset[lst].indep ^= 1;
		lst = par[lst];
	} while (lst != -1);
	iset.clear();
	F0R(i,sz(gset)) if (gset[i].indep) 
		gset[i].ipos = sz(iset), iset.pb(i);
	return 1; // increased sz(iset) by 1
}
int solve() {
	m.clear(); gset.clear(); iset.clear();
	int R; cin >> R; if (!R) exit(0); // # edges
	colUsed.rsz(R); basisWo.rsz(R);
	F0R(i,R) { // edges (a,b) and (c,d) of same col
		int a,b,c,d; cin >> a >> b >> c >> d; 
		gset.pb(Element(a,b,i)), gset.pb(Element(c,d,i));
		m[a] = m[b] = m[c] = m[d] = 0;
	}
	int co = 0; trav(t,m) t.s = co++;
	trav(t,gset) t.ed.f = m[t.ed.f], t.ed.s = m[t.ed.s];
	while (augment()); // keep increasing size of indep set
	return 2*sz(iset);
}
/// while (1) ps(solve());
