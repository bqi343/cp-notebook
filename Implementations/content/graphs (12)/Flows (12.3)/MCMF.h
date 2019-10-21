/**
 * Description: Min-Cost Max Flow, no negative cycles allowed
 * Time: O(NM^2\log M)
 * Source: GeeksForGeeks
 * Verification: https://codeforces.com/contest/164/problem/C
 */

template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;
template<class T> T poll(pqg<T>& x) {
	T y = x.top(); x.pop();
	return y;
}

template<int SZ> struct mcmf { 
	typedef ll F; typedef ll C;
	struct Edge { int to, rev; F flow, cap; C cost; int id; };
	vector<Edge> adj[SZ];
	void addEdge(int u, int v, F cap, C cost) {
		assert(cap >= 0);
		Edge a{v, sz(adj[v]), 0, cap, cost}, b{u, sz(adj[u]), 0, 0, -cost};
		adj[u].pb(a), adj[v].pb(b);
	}

	int N, s, t;
	pi pre[SZ]; // previous vertex, edge label on path
	pair<C,F> cost[SZ]; // tot cost of path, amount of flow
	C totCost, curCost; F totFlow; 
	void reweight() { // makes all edge costs non-negative
		// all edges on shortest path become 0
		F0R(i,N) trav(p,adj[i]) p.cost += cost[i].f-cost[p.to].f;
	}
	bool spfa() { // reweight ensures that there will be negative weights 
		// only during the first time you run this
		F0R(i,N) cost[i] = {INF,0}; cost[s] = {0,INF};
		pqg<pair<C,int>> todo; todo.push({0,s});
		while (sz(todo)) {
			auto x = poll(todo); if (x.f > cost[x.s].f) continue;
			trav(a,adj[x.s]) if (x.f+a.cost < cost[a.to].f && a.flow < a.cap) { 
				// if costs are doubles, add some EPS to ensure that 
				// you do not traverse some 0-weight cycle repeatedly
				pre[a.to] = {x.s,a.rev};
				cost[a.to] = {x.f+a.cost,min(a.cap-a.flow,cost[x.s].s)};
				todo.push({cost[a.to].f,a.to});
			}
		}
		curCost += cost[t].f; return cost[t].s;
	}
	void backtrack() {
		F df = cost[t].s; totFlow += df, totCost += curCost*df;
		for (int x = t; x != s; x = pre[x].f) {
			adj[x][pre[x].s].flow -= df;
			adj[pre[x].f][adj[x][pre[x].s].rev].flow += df;
		}
	}
	pair<F,C> calc(int _N, int _s, int _t) {
		N = _N; s = _s, t = _t; totFlow = totCost = curCost = 0;
		while (spfa()) reweight(), backtrack();
		return {totFlow, totCost};
	}
};