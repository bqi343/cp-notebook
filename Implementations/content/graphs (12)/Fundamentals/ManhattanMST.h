/**
 * Description: Compute minimum spanning tree of points where edges are manhattan distances 
 * Time: O(N\log N)
 * Source: Rezwan Arefin
 * Verification: 
	* https://open.kattis.com/problems/gridmst
	* CSA 84 The Sprawl
	* TC 760 ComponentsForever
 */

#include "MST.h"

int N;
vector<array<int,3>> cur;
vector<pair<ll,pi>> ed;
vi ind;

struct {
	map<int,pi> m;
	void upd(int a, pi b) { 
		auto it = m.lb(a);
		if (it != m.end() && it->s <= b) return;
		m[a] = b; it = m.find(a);
		while (it != m.begin() && prev(it)->s >= b) m.erase(prev(it));
	}
	pi query(int y) { // for all a > y find min possible value of b 
		auto it = m.ub(y);
		if (it == m.end()) return {2*MOD,2*MOD};
		return it->s;
	}
} S;

void solve() {
	sort(all(ind),[](int a, int b) { return cur[a][0] > cur[b][0]; });
	S.m.clear();
	int nex = 0;
	trav(x,ind) { // cur[x][0] <= ?, cur[x][1] < ? 
		while (nex < N && cur[ind[nex]][0] >= cur[x][0]) {
			int b = ind[nex++]; 
			S.upd(cur[b][1],{cur[b][2],b});
		}
		pi t = S.query(cur[x][1]);
		if (t.s != 2*MOD) ed.pb({(ll)t.f-cur[x][2],{x,t.s}});
	}
}

ll mst(vpi v) {
	N = sz(v); cur.resz(N); ed.clear(); 
	ind.clear(); F0R(i,N) ind.pb(i);
	sort(all(ind),[&v](int a, int b) { return v[a] < v[b]; });
	F0R(i,N-1) if (v[ind[i]] == v[ind[i+1]]) ed.pb({0,{ind[i],ind[i+1]}});
	F0R(i,2) { // it's probably ok to consider just two quadrants?
		F0R(i,N) {
			auto a = v[i];
			cur[i][2] = a.f+a.s;
		}
		F0R(i,N) { // first octant
			auto a = v[i];
			cur[i][0] = a.f-a.s;
			cur[i][1] = a.s;
		}
		solve();
		F0R(i,N) { // second octant
			auto a = v[i];
			cur[i][0] = a.f;
			cur[i][1] = a.s-a.f;
		}
		solve();
		trav(a,v) a = {a.s,-a.f}; // rotate 90 degrees, repeat
	}
	return kruskal(ed);
}
