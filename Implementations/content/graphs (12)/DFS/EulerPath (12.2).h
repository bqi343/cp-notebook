/**
 * Description: Eulerian path for both directed and undirected graphs,
 	* if it exists.
 * Time: $O(N+M)$ 
 * Source: 
	* USACO Training
	* MIT ICPC Notebook
 * Verification:
	* directed -> https://open.kattis.com/problems/eulerianpath
	* undirected -> USACO Training 3.3, Riding the Fences
 */

template<int SZ, bool directed> struct Euler {
	int N, M = 0;
	vpi adj[SZ]; vpi::iterator its[SZ];
	vector<bool> used;
	void ae(int a, int b) {
		if (directed) adj[a].pb({b,M});
		else adj[a].pb({b,M}), adj[b].pb({a,M});
		used.pb(0); M ++;
	}
	vpi solve(int _N, int src = 1) {
		N = _N; FOR(i,1,N+1) its[i] = begin(adj[i]);
		vector<pair<pi,int>> ret, s = {{{src,-1},-1}};
		while (sz(s)) {
			int x = s.bk.f.f;
			auto& it = its[x], en = end(adj[x]);
			while (it != en && used[it->s]) it ++;
			if (it == en) { 
				if (sz(ret) && ret.bk.f.s != s.bk.f.f) return {}; 
				ret.pb(s.bk), s.pop_back(); 
			} else { s.pb({{it->f,x},it->s}); used[it->s] = 1; }
		}
		if (sz(ret) != M+1) return {};
		vpi ans; trav(t,ret) ans.pb({t.f.f,t.s});
		reverse(all(ans)); return ans;
	}
};
