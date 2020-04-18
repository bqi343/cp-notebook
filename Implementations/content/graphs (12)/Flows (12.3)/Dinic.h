/**
 * Description: Fast flow. After computing flow, edges $\{u,v\}$ such that 
	* $lev[u] \neq -1,$ $lev[v] = -1$ are part of min cut.
	* Use \texttt{reset} and \texttt{rcap} for Gomory-Hu.
 * Time: $O(N^2M)$ flow, $O(M\sqrt N)$ bipartite matching
 * Source: GeeksForGeeks, Chilli
 * Verification: RMI 2017 Day 1 Fashion
	* https://pastebin.com/VJxTvEg1
 */

template<int SZ> struct Dinic {
	int N,s,t; // # verts, source, sink
	typedef ll F; // flow type
	struct Edge { int to, rev; F flo, cap; };
	vector<Edge> adj[SZ]; // use asserts, don't be dumb
	void reset() { F0R(i,N) trav(e,adj[i]) e.flo = 0; }
	void ae(int u, int v, F cap, F rcap = 0) { 
		assert(min(cap,rcap) >= 0); 
		Edge a{v,sz(adj[v]),0,cap}, b{u,sz(adj[u]),0,rcap};
		adj[u].pb(a), adj[v].pb(b); } 
	int lev[SZ]; typename vector<Edge>::iterator cur[SZ]; 
	bool bfs() { // level = shortest distance from source
		F0R(i,N) lev[i] = -1, cur[i] = begin(adj[i]);
		queue<int> q({s}); lev[s] = 0; 
		while (sz(q)) {
			int u = q.ft; q.pop();
			trav(e,adj[u]) if (lev[e.to] < 0 && e.flo < e.cap) 
				q.push(e.to), lev[e.to] = lev[u]+1;
		}
		return lev[t] >= 0;
	}
	F dfs(int v, F flo) {
		if (v == t) return flo;
		for (; cur[v] != end(adj[v]); cur[v]++) {
			Edge& e = *cur[v];
			if (lev[e.to]!=lev[v]+1||e.flo==e.cap) continue;
			F df = dfs(e.to,min(flo,e.cap-e.flo));
			if (df) { e.flo += df; adj[e.to][e.rev].flo -= df;
				return df; } // saturated >=1 one edge
		}
		return 0;
	}
	F maxFlow(int _N, int _s, int _t) {
		N = _N, s = _s, t = _t; assert(s != t);
		F tot = 0; while (bfs()) while (F df = 
			dfs(s,numeric_limits<F>::max())) tot += df;
		return tot;
	}
};