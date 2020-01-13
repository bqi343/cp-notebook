/**
 * Description: Minimum-cost maximum flow, assumes no negative cycles. 
 	* Edges may be negative only during first run of SPFA.
 * Time: $O(FM\log M)$ if caps are integers and $F$ is max flow
 * Source: GeeksForGeeks
 	* https://courses.csail.mit.edu/6.854/06/scribe/s12-minCostFlowAlg.pdf
 	* running time is only pseudo-polynomial; see https://codeforces.com/blog/entry/70740
 * Verification: https://codeforces.com/contest/164/problem/C
 */

template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;
template<class T> T poll(pqg<T>& x) {
	T y = x.top(); x.pop(); return y; }

template<int SZ> struct MCMF { 
	typedef ll F; typedef ll C;
	struct Edge { int to, rev; F flow, cap; C cost; };
	vector<Edge> adj[SZ];
	void ae(int u, int v, F cap, C cost) {
		assert(cap >= 0);
		Edge a{v,sz(adj[v]),0,cap,cost}, b{u,sz(adj[u]),0,0,-cost};
		adj[u].pb(a), adj[v].pb(b);
	}
	int N, s, t;
	pi pre[SZ]; // previous vertex, edge label on path
	pair<C,F> cost[SZ]; // tot cost of path, amount of flow
	C totCost, curCost; F totFlow; 
	bool spfa() { // find lowest cost path to send flow through
		F0R(i,N) cost[i] = {numeric_limits<C>::max(),0}; 
		cost[s] = {0,numeric_limits<F>::max()};
		pqg<pair<C,int>> todo; todo.push({0,s});
		while (sz(todo)) {
			auto x = poll(todo); if (x.f > cost[x.s].f) continue;
			trav(a,adj[x.s]) if (a.flow < a.cap 
				&& ckmin(cost[a.to].f,x.f+a.cost)) { 
				// if costs are doubles, add some small constant so
				// you don't traverse some ~0-weight cycle repeatedly
				pre[a.to] = {x.s,a.rev};
				cost[a.to].s = min(a.cap-a.flow,cost[x.s].s);
				todo.push({cost[a.to].f,a.to});
			}
		}
		return cost[t].s;
	}
	void backtrack() {
		F df = cost[t].s; totFlow += df;
		curCost += cost[t].f; totCost += curCost*df;
		for (int x = t; x != s; x = pre[x].f) {
			adj[x][pre[x].s].flow -= df;
			adj[pre[x].f][adj[x][pre[x].s].rev].flow += df;
		}
		F0R(i,N) trav(p,adj[i]) p.cost += cost[i].f-cost[p.to].f;
		// all reduced costs non-negative
		// edges on shortest path become 0
	}
	pair<F,C> calc(int _N, int _s, int _t) {
		N = _N; s = _s, t = _t; totFlow = totCost = curCost = 0;
		while (spfa()) backtrack();
		return {totFlow,totCost};
	}
};
