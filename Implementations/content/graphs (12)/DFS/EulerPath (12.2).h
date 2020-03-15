/**
 * Description: Eulerian path starting at \texttt{src} if it exists, 
 	* visits all edges exactly once. Works for both directed and 
 	* undirected. Returns vector of \{vertex,label of edge to vertex\}.
 	* The second element of the first pair is always $-1$.
 * Time: O(N+M)
 * Source: USACO Training, MIT ICPC Notebook
 * Verification:
	* directed -> https://open.kattis.com/problems/eulerianpath
	* undirected -> USACO Training 3.3, Riding the Fences
 */

template<int SZ, bool directed> struct Euler {
	int N; vpi adj[SZ]; vpi::iterator its[SZ];
	vector<bool> used;
	void ae(int a, int b) {
		int M = sz(used); used.pb(0); 
		adj[a].eb(b,M); if (!directed) adj[b].eb(a,M);
	}
	vpi solve(int _N, int src = 0) {
		N = _N; F0R(i,N) its[i] = begin(adj[i]);
		vector<pair<pi,int>> ret, s = {{{src,-1},-1}}; 
		// {{vert, prev vert}, edge label}
		while (sz(s)) {
			int x = s.bk.f.f; auto& it = its[x], en = end(adj[x]);
			while (it != en && used[it->s]) it ++;
			if (it == en) { // no more edges out of vertex
				if (sz(ret) && ret.bk.f.s != x) return {}; 
				ret.pb(s.bk), s.pop_back(); 
			} else { s.pb({{it->f,x},it->s}); used[it->s] = 1; }
		}
		if (sz(ret) != sz(used)+1) return {};
		vpi ans; trav(t,ret) ans.pb({t.f.f,t.s});
		reverse(all(ans)); return ans;
	}
};