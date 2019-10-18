/**
 * Description: Compute max flow between every pair of vertices of 
 * undirected graph
 * Source: Own
 * Verification: https://codeforces.com/problemset/problem/343/E
 */

#include "Dinic.h"

template<int SZ> struct GomoryHu {
	int N;
	vector<pair<pi,int>> ed;
	void addEdge(int a, int b, int c) { ed.pb({{a,b},c}); }

	vector<vi> cor = {{}}; // groups of vertices
	map<int,int> adj[2*SZ]; // current edges of tree
	int side[SZ];

	int gen(vector<vi> cc) {
		Dinic<SZ> D = Dinic<SZ>();
		vi comp(N+1); F0R(i,sz(cc)) trav(t,cc[i]) comp[t] = i;
		trav(t,ed) if (comp[t.f.f] != comp[t.f.s]) {
			D.addEdge(comp[t.f.f],comp[t.f.s],t.s);
			D.addEdge(comp[t.f.s],comp[t.f.f],t.s);
		}
		int f = D.maxFlow(0,1); 
		F0R(i,sz(cc)) trav(j,cc[i]) side[j] = D.level[i] >= 0; // min cut
		return f;
	}

	void fill(vi& v, int a, int b) {
		trav(t,cor[a]) v.pb(t);
		trav(t,adj[a]) if (t.f != b) fill(v,t.f,a);
	}

	void addTree(int a, int b, int c) { adj[a][b] = c, adj[b][a] = c; }
	void delTree(int a, int b) { adj[a].erase(b), adj[b].erase(a); }

	vector<pair<pi,int>> init(int _N) { // returns edges of Gomory-Hu Tree
		N = _N;
		FOR(i,1,N+1) cor[0].pb(i);
		queue<int> todo; todo.push(0); 
		while (sz(todo)) {
			int x = todo.front(); todo.pop();
			vector<vi> cc; trav(t,cor[x]) cc.pb({t});
			trav(t,adj[x]) {
				cc.pb({});
				fill(cc.back(),t.f,x);
			}
			int f = gen(cc); // run max flow
			cor.pb({}), cor.pb({});
			trav(t,cor[x]) cor[sz(cor)-2+side[t]].pb(t);
			F0R(i,2) if (sz(cor[sz(cor)-2+i]) > 1) todo.push(sz(cor)-2+i);
			F0R(i,sz(cor)-2) if (i != x && adj[i].count(x)) {
				addTree(i,sz(cor)-2+side[cor[i][0]],adj[i][x]);
				delTree(i,x);
			} // modify tree edges
			addTree(sz(cor)-2,sz(cor)-1,f);
		}
		vector<pair<pi,int>> ans;
		F0R(i,sz(cor)) trav(j,adj[i]) if (i < j.f) 
			ans.pb({{cor[i][0],cor[j.f][0]},j.s});
		return ans;
	}
};