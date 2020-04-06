/**
 * Description: Minimum-cost maximum flow, assumes no negative cycles. 
 	* Edges may be negative only during first run of SPFA. To get flow
 	* through original edges, assign ID's during \texttt{ae}.
 * Time: $O(FM\log M)$ if caps are integers and $F$ is max flow
 * Source: GeeksForGeeks
 	* https://courses.csail.mit.edu/6.854/06/scribe/s12-minCostFlowAlg.pdf
 	* running time is only pseudo-polynomial; see https://codeforces.com/blog/entry/70740
 * Verification: https://codeforces.com/contest/164/problem/C
 */

template<int SZ> struct MCMF {
	int N,s,t; // # verts, source, sink
	typedef ll F; typedef ll C; // flow type, cost type
	struct Edge { int to, rev; F flow, cap; C cost; };
	vector<Edge> adj[SZ]; // use asserts, don't try smth dumb
	void ae(int u, int v, F cap, C cost) { assert(cap >= 0); 
		Edge a{v,sz(adj[v]),0,cap,cost}, b{u,sz(adj[u]),0,0,-cost};
		adj[u].pb(a), adj[v].pb(b); }
	pi pre[SZ]; // previous vertex, edge label on path
	pair<C,F> cost[SZ]; // tot cost of path, amount of flow
	C totCost = 0, curCost = 0; F totFlow = 0; 
	bool spfa() { // find lowest cost path to send flow through
		F0R(i,N) cost[i] = {numeric_limits<C>::max(),0}; 
		cost[s] = {0,numeric_limits<F>::max()};
		typedef pair<C,int> T;
		priority_queue<T,vector<T>,greater<T>> todo; 
		todo.push({0,s});
		while (sz(todo)) {
			T x = todo.top(); todo.pop(); 
			if (x.f > cost[x.s].f) continue;
			trav(a,adj[x.s]) if (a.flow < a.cap 
				&& ckmin(cost[a.to].f,x.f+a.cost)) { 
				pre[a.to] = {x.s,a.rev};
				cost[a.to].s = min(a.cap-a.flow,cost[x.s].s);
				todo.push({cost[a.to].f,a.to});
			} // if costs are doubles, add some EPS so you 
		} // don't traverse ~0-weight cycle repeatedly
		return cost[t].s; // return flow
	}
	void backtrack() {
		F df = cost[t].s; totFlow += df;
		curCost += cost[t].f; totCost += curCost*df;
		for (int x = t; x != s; x = pre[x].f) {
			adj[x][pre[x].s].flow -= df;
			adj[pre[x].f][adj[x][pre[x].s].rev].flow += df;
		}
		F0R(i,N) trav(p,adj[i]) p.cost += cost[i].f-cost[p.to].f;
	} // all reduced costs non-negative if flow > 0
	// edges on shortest path become 0
	pair<F,C> calc(int _N, int _s, int _t) {
		N = _N, s = _s, t = _t; assert(s != t);
		while (spfa()) backtrack();
		return {totFlow,totCost};
	}
};