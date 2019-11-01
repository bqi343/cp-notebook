/**
 * Description: fast flow
 * Time: $O(N^2M)$ flow, $O(M\sqrt N)$ bipartite matching
 * Source: GeeksForGeeks, Chilli
 * Verification: RMI 2017 Day 1 Fashion
	* https://pastebin.com/VJxTvEg1
 */

template<int SZ> struct Dinic {
	typedef ll F; // flow type
	struct Edge { int to, rev; F flow, cap; };
	int N,s,t;
	vector<Edge> adj[SZ];
	typename vector<Edge>::iterator cur[SZ];
	void addEdge(int u, int v, F cap) {
		assert(cap >= 0); // don't try smth dumb
		Edge a{v, sz(adj[v]), 0, cap}, b{u, sz(adj[u]), 0, 0};
		adj[u].pb(a), adj[v].pb(b);
	}
	int level[SZ];
	bool bfs() { // level = shortest distance from source
		// after computing flow, edges {u,v} such that level[u] \neq -1, level[v] = -1 are part of min cut
		F0R(i,N) level[i] = -1, cur[i] = begin(adj[i]);
		queue<int> q({s}); level[s] = 0; 
		while (sz(q)) {
			int u = q.front(); q.pop();
			trav(e,adj[u]) if (level[e.to] < 0 && e.flow < e.cap) 
				q.push(e.to), level[e.to] = level[u]+1;
		}
		return level[t] >= 0;
	}
	F sendFlow(int v, F flow) {
		if (v == t) return flow;
		for (; cur[v] != end(adj[v]); cur[v]++) {
			Edge& e = *cur[v];
			if (level[e.to] != level[v]+1 || e.flow == e.cap) continue;
			auto df = sendFlow(e.to,min(flow,e.cap-e.flow));
			if (df) { // saturated at least one edge
				e.flow += df; adj[e.to][e.rev].flow -= df;
				return df;
			}
		}
		return 0;
	}
	F maxFlow(int _N, int _s, int _t) {
		N = _N, s = _s, t = _t; if (s == t) return -1;
		F tot = 0;
		while (bfs()) while (auto df = sendFlow(s,numeric_limits<F>::max())) tot += df;
		return tot;
	}
};