/**
 * Description: Fast flow. After computing flow, edges $\{u,v\}$ such that 
	* $lev[u] \neq 0,$ $lev[v] = 0$ are part of min cut.
	* Use \texttt{reset} and \texttt{rcap} for Gomory-Hu.
 * Time: $O(N^2M)$ flow, $O(M\sqrt N)$ bipartite matching
 * Source: GeeksForGeeks, Chilli
 	* https://codeforces.com/contest/1416/submission/94013395
 * Verification: RMI 2017 Day 1 Fashion
	* https://pastebin.com/VJxTvEg1
 */

struct Dinic {
	using F = ll; // flow type
	struct Edge { int to, rev; F flo, cap; };
	int N; V<V<Edge>> adj;
	void init(int _N) { N = _N; adj.rsz(N); }
	/// void reset() { F0R(i,N) each(e,adj[i]) e.flo = 0; }
	void ae(int a, int b, F cap, F rcap = 0) { assert(min(cap,rcap) >= 0); 
		adj[a].pb({b,sz(adj[b]),0,cap});
		adj[b].pb({a,sz(adj[a])-1,0,rcap});
	}
	vi lev, ptr;
	bool bfs(int s, int t) { // level = shortest distance from source
		lev = ptr = vi(N);
		lev[s] = 1; queue<int> q({s});
		while (sz(q)) { int u = q.ft; q.pop();
			each(e,adj[u]) if (e.flo < e.cap && !lev[e.to])
				q.push(e.to), lev[e.to] = lev[u]+1;
		}
		return lev[t];
	}
	F dfs(int v, int t, F flo) {
		if (v == t) return flo;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i]; F dif = e.cap-e.flo;
			if (lev[e.to]!=lev[v]+1||!dif) continue;
			if (F df = dfs(e.to,t,min(flo,dif))) { 
				e.flo += df; adj[e.to][e.rev].flo -= df;
				return df; } // saturated >=1 one edge
		}
		return 0;
	}
	F maxFlow(int s, int t) {
		F tot = 0; while (bfs(s,t)) while (F df = 
			dfs(s,t,numeric_limits<F>::max())) tot += df;
		return tot;
	}
};
