/**
 * Description: Heavy Light Decomposition
 * Time: $O(\log^2 N)$ per path operations
 * Source: http://codeforces.com/blog/entry/22072, https://codeforces.com/blog/entry/53170
 * Verification: USACO Grass Planting, https://www.hackerrank.com/challenges/subtrees-and-paths
 */

template<int SZ, bool VALUES_IN_EDGES> struct HLD { 
	int N; vi adj[SZ];
	int par[SZ], sz[SZ], depth[SZ];
	int root[SZ], pos[SZ];
	LazySegTree<ll,SZ> tree;
	void addEdge(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
	
	void dfs_sz(int v = 1) {
		if (par[v]) adj[v].erase(find(all(adj[v]),par[v]));
		sz[v] = 1;
		trav(u,adj[v]) {
			par[u] = v; depth[u] = depth[v]+1;
			dfs_sz(u); sz[v] += sz[u];
			if (sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfs_hld(int v = 1) {
		static int t = 0;
		pos[v] = t++;
		trav(u,adj[v]) {
			root[u] = (u == adj[v][0] ? root[v] : u);
			dfs_hld(u);
		}
	}
	void init(int _N) {
		N = _N; par[1] = depth[1] = 0; root[1] = 1; 
		dfs_sz(); dfs_hld();
	}

	template <class BinaryOperation>
	void processPath(int u, int v, BinaryOperation op) {
		for (; root[u] != root[v]; v = par[root[v]]) {
			if (depth[root[u]] > depth[root[v]]) swap(u, v);
			op(pos[root[v]], pos[v]);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u]+VALUES_IN_EDGES, pos[v]); 
	}

	void modifyPath(int u, int v, int val) { // add val to vertices/edges along path
		processPath(u, v, [this, &val](int l, int r) { tree.upd(l, r, val); });
	}
	void modifySubtree(int v, int val) { // add val to vertices/edges in subtree
		tree.upd(pos[v]+VALUES_IN_EDGES,pos[v]+sz[v]-1,val);
	}
	ll queryPath(int u, int v) { // query sum of path
		ll res = 0; processPath(u, v, [this, &res](int l, int r) { res += tree.qsum(l, r); });
		return res;
	}
};