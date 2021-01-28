/** 
 * Description: 2-Edge-Connected Components
 * Time: O((M+N)\log N)
 * Source: Own
 * Verification: https://judge.yosupo.jp/problem/two_edge_connected_components
 */
 
struct TwoEdgeCC {
	struct {
		vi e; void init(int n) { e = vi(n,-1); }
		int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
		bool unite(int x, int y) { // set par[y] = x
			x = get(x), y = get(y); if (x == y) return 0;
			e[x] += e[y]; e[y] = x; return 1;
		}
	} DSU;
	int N; vector<vi> adj; vi depth, par;
	vpi extra;
	void init(int _N) {
		N = _N; DSU.init(N);
		adj.rsz(N), depth.rsz(N), par = vi(N,-1);
	}
	void dfs(int x) {
		each(t,adj[x]) if (t != par[x]) 
			par[t] = x, depth[t] = depth[x]+1, dfs(t);
	}
	void ae(int a, int b) {
		if (DSU.unite(a,b)) adj[a].pb(b), adj[b].pb(a); // tree edge
		else extra.pb({a,b});
	}
	void ad(int a, int b) { // OK
		while (1) {
			a = DSU.get(a), b = DSU.get(b);
			if (a == b) return;
			if (depth[a] < depth[b]) swap(a,b);
			assert(par[a] != -1 && DSU.unite(par[a],a));
		}
	}
	void gen() {
		F0R(i,N) if (par[i] == -1) dfs(i);
		DSU.init(N); // again!
		each(t,extra) ad(t.f,t.s);
	}
};
