/**
 * Description: Computes a set of maximum size which is independent 
 	* in both graphic and colorful matroids, aka a spanning forest where
 	* no two edges are of the same color. In general, construct the exchange
 	* graph and find a shortest path.
 * Time: $O(GI^{1.5})$ calls to oracles, where $G$ is size of ground set 
 	* and $I$ is size of independent set.
 * Source: https://codeforces.com/blog/entry/69287
 * Verification: https://www.spoj.com/problems/COIN/
 */

#include "../graphs (12)/DSU/DSU (7.6).h"

struct Element {
	pi ed; int col;
	bool indep = 0; int ipos; // independent set pos
	Element(int u, int v, int c) { ed = {u,v}; col = c; }
};
vector<Element> gset; vi iset; // ground set, independent set

int verts; // graphic matroid
struct GBasis { 
	DSU D; GBasis() { D.init(verts); } 
	void add(pi v) { assert(D.unite(v.f,v.s)); }
	bool indep(pi v) { return !D.sameSet(v.f,v.s); }
};
GBasis basis; vector<GBasis> basisWo; // basis without
bool graphOracle(int ins) { return basis.indep(gset[ins].ed); }
bool graphOracle(int ins, int rem) {
	return basisWo[gset[rem].ipos].indep(gset[ins].ed); }
void prepGraphOracle() {
	basis = GBasis(); basisWo.assign(sz(iset),GBasis());
	F0R(i,sz(iset)) {
		pi v = gset[iset[i]].ed; basis.add(v);
		F0R(j,sz(iset)) if (i != j) basisWo[j].add(v);
	}
}
int cols; vector<bool> colUsed; // colorful matroid
bool colorOracle(int ins) { 
	ins = gset[ins].col; return !colUsed[ins]; }
bool colorOracle(int ins, int rem) {
	ins = gset[ins].col, rem = gset[rem].col;
	return !colUsed[ins] || ins == rem; }
void prepColorOracle() {
	colUsed.assign(cols,0);
	each(t,iset) colUsed[gset[t].col] = 1; }
 
bool augment() {
	prepGraphOracle(); prepColorOracle();
	vi par(sz(gset),-2); queue<int> q;
	F0R(i,sz(gset)) if (!gset[i].indep && colorOracle(i)) 
		par[i] = -1, q.push(i);
	int lst = -1;
	while (sz(q)) {
		int cur = q.ft; q.pop();
		if (gset[cur].indep) {
			F0R(to,sz(gset)) if (!gset[to].indep && par[to] == -2) {
				if (!colorOracle(to,cur)) continue;
				par[to] = cur; q.push(to);
			}
		} else {
			if (graphOracle(cur)) { lst = cur; break;	}
			each(to,iset) if (par[to] == -2) {
				if (!graphOracle(cur,to)) continue;
				par[to] = cur; q.push(to);
			}
		}
	}
	if (lst == -1) return 0;
	do { gset[lst].indep^=1, lst=par[lst]; } while (lst!=-1);
	iset.clear(); F0R(i,sz(gset)) if (gset[i].indep) 
		gset[i].ipos = sz(iset), iset.pb(i);
	return 1; // increased sz(iset) by 1
}
int calc() {
	iset.clear(); verts = cols = 0;
	each(g,gset) { ckmax(verts,max(g.ed.f,g.ed.s)+1);
		ckmax(cols,g.col+1); }
	while (augment()); // keep increasing size of indep set
	return sz(iset);
}

/**int solve() {
	gset.clear(); 
	int R; cin >> R; if (!R) exit(0);
	map<int,int> m;
	F0R(i,R) { // edges (a,b) and (c,d) of same col
		int a,b,c,d; cin >> a >> b >> c >> d; 
		gset.eb(a,b,i), gset.eb(c,d,i);
		m[a] = m[b] = m[c] = m[d] = 0;
	}
	int co = 0; each(t,m) t.s = co++;
	each(t,gset) t.ed.f = m[t.ed.f], t.ed.s = m[t.ed.s];
	return calc();
}
int main() {
	while (1) ps(2*solve());
}*/
