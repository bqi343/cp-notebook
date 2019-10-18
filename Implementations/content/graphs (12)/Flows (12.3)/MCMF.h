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
	struct Edge { int to, rev; ll f, c, cost; };
	vector<Edge> adj[SZ];
	void addEdge(int u, int v, ll cap, ll cost) {
		assert(cap >= 0);
		Edge a{v, sz(adj[v]), 0, cap, cost}, b{u, sz(adj[u]), 0, 0, -cost};
		adj[u].pb(a), adj[v].pb(b);
	}

	int N, s, t;
	pi pre[SZ]; // previous vertex, edge label on path
	pl cost[SZ]; // tot cost of path, amount of flow
	ll totFlow, totCost, curCost;
	void reweight() { 
		// ensures all non-negative edge weights, destroys original
		F0R(i,N) trav(p,adj[i]) p.cost += cost[i].f-cost[p.to].f;
	}
	bool spfa() { // reweighting will ensure that there will be negative weights only during the first time you run this
		F0R(i,N) cost[i] = {INF,0};
		cost[s] = {0,INF};
		pqg<pair<ll,int>> todo({{0,s}});
		while (sz(todo)) {
			auto x = poll(todo); if (x.f > cost[x.s].f) continue;
			trav(a,adj[x.s]) if (x.f+a.cost < cost[a.to].f && a.f < a.c) {
				pre[a.to] = {x.s,a.rev};
				cost[a.to] = {x.f+a.cost, min(a.c-a.f,cost[x.s].s)};
				todo.push({cost[a.to].f,a.to});
			}
		}
		curCost += cost[t].f; return cost[t].s;
	}
	void backtrack() {
		auto f = cost[t].s; totFlow += f, totCost += curCost*f;
		for (int x = t; x != s; x = pre[x].f) {
			adj[x][pre[x].s].f -= f;
			adj[pre[x].f][adj[x][pre[x].s].rev].f += f;
		}
	}

	pl calc(int _N, int _s, int _t) {
		N = _N; s = _s, t = _t; totFlow = totCost = curCost = 0;
		spfa();
		while (1) {
			reweight();
			if (!spfa()) return {totFlow, totCost};
			backtrack();
		}
	}
};
