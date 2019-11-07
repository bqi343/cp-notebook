/**
 * Description: Returns edges of Gomory-Hu tree. Max flow between 
	* pair of vertices of undirected graph is given by min edge
	* weight along tree path. Uses the lemma that for any $i,j,k,$
	* $\lambda_{ik}\ge \min(\lambda_{ij},\lambda_{jk}),$ 
	* where $\lambda_{ij}$ denotes the flow from $i$ to $j.$
 * Source: https://github.com/koosaga/DeobureoMinkyuParty/blob/master/teamnote.tex
 * Time: $O(N)$ calls to Dinic
 * Verification: https://codeforces.com/problemset/problem/343/E
 */

#include "Dinic.h"

template<int SZ> struct GomoryHu {
	vector<pair<pi,int>> ed;
	void addEdge(int a, int b, int c) { ed.pb({{a,b},c}); }
	vector<pair<pi,int>> init(int N) { 
		vpi ret(N+1,mp(1,0));
		FOR(i,2,N+1) {
			Dinic<SZ> D;
			trav(t,ed) {
				D.addEdge(t.f.f,t.f.s,t.s); 
				D.addEdge(t.f.s,t.f.f,t.s);
			}
			ret[i].s = D.maxFlow(N+1,i,ret[i].f);
			FOR(j,i+1,N+1) if (ret[j].f == ret[i].f 
				&& D.level[j] != -1) ret[j].f = i;
		}
		vector<pair<pi,int>> res;
		FOR(i,2,N+1) res.pb({{i,ret[i].f},ret[i].s});
		return res;
	}
};