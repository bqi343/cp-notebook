/**
 * Description: Minimum-cost maximum flow, assumes no negative cycles. 
 	* It is possible to choose negative edge costs such that the first 
 	* run of Dijkstra is slow, but this hasn't been an issue in the past. 
 	* Edge weights $\ge 0$ for every subsequent run. To get flow through 
 	* original edges, assign ID's during \texttt{ae}.
 * Time: Ignoring first run of Dijkstra, $O(FM\log M)$ 
 	* if caps are integers and $F$ is max flow.
 * Source: GeeksForGeeks
 	* https://courses.csail.mit.edu/6.854/06/scribe/s12-minCostFlowAlg.pdf
 	* running time is only pseudo-polynomial; see https://codeforces.com/blog/entry/70740
 	* https://en.wikipedia.org/wiki/Johnson%27s_algorithm (to get non-negative weights)
 * Verification: https://codeforces.com/contest/164/problem/C
 	* https://codeforces.com/contest/316/problem/C2
 		* TLEs, don't use priority queue
 */

template<int SZ> struct MCMF {
	int N,s,t; // # verts, source, sink
	using F = ll; using C = ll; // flow type, cost type
	struct Edge { int to, rev; F flow, cap; C cost; };
	vector<Edge> adj[SZ]; // use asserts, don't try smth dumb
	void ae(int u, int v, F cap, C cost) { assert(cap >= 0); 
		Edge a{v,sz(adj[v]),0,cap,cost}, b{u,sz(adj[u]),0,0,-cost};
		adj[u].pb(a), adj[v].pb(b); }
	pi pre[SZ]; // previous vertex, edge label on path
	C dist[SZ], totCost = 0, curCost = 0; // tot cost of path
	F totFlow = 0; 
	bool path() { // find lowest cost path to send flow through
		F0R(i,N) dist[i] = numeric_limits<C>::max();
		using T = pair<C,int>; priority_queue<T,vector<T>,greater<T>> todo; 
		todo.push({dist[s] = 0,s}); 
		while (sz(todo)) { // Dijkstra
			T x = todo.top(); todo.pop(); if (x.f > dist[x.s]) continue;
			trav(a,adj[x.s]) if (a.flow < a.cap && ckmin(dist[a.to],x.f+a.cost))
				pre[a.to] = {x.s,a.rev}, todo.push({dist[a.to],a.to});
		} // if costs are doubles, add some EPS so you 
		// don't traverse ~0-weight cycle repeatedly
		return dist[t] != numeric_limits<C>::max(); // return flow
	}
	void backtrack() {
		F df = numeric_limits<F>::max();
		for (int x = t; x != s; x = pre[x].f) {
			const Edge& e = adj[pre[x].f][adj[x][pre[x].s].rev];
			ckmin(df,e.cap-e.flow);
		} // get max flow you can send along path
		totFlow += df; curCost += dist[t]; totCost += curCost*df;
		for (int x = t; x != s; x = pre[x].f) { // subtract from cap,
			adj[x][pre[x].s].flow -= df; // add two reverse edges
			adj[pre[x].f][adj[x][pre[x].s].rev].flow += df;
		}
		F0R(i,N) trav(p,adj[i]) p.cost += dist[i]-dist[p.to]; // make dists non-negative
	} // all reduced costs non-negative if flow > 0
	// edges on shortest path become 0
	pair<F,C> calc(int _N, int _s, int _t) {
		N = _N, s = _s, t = _t; assert(s != t);
		while (path()) backtrack();
		return {totFlow,totCost};
	}
};