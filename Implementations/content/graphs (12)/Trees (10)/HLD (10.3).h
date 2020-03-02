/**
 * Description: Heavy-Light Decomposition, add val to verts 
 	* and query sum in path/subtree
 * Time: any tree path is split into $O(\log N)$ parts
 * Source: http://codeforces.com/blog/entry/22072, https://codeforces.com/blog/entry/53170
 * Verification: USACO Grass Planting, https://www.hackerrank.com/challenges/subtrees-and-paths
 */

#include "../../data-structures/1D Range Queries (9.2)/LazySeg (15.2).h"

template<int SZ, bool VALS_IN_EDGES> struct HLD { 
	int N; vi adj[SZ];
	int par[SZ], sz[SZ], depth[SZ];
	int root[SZ], pos[SZ]; /// vi rpos;
	void ae(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
	void dfsSz(int v = 1) {
		if (par[v]) adj[v].erase(find(all(adj[v]),par[v]));
		sz[v] = 1;
		trav(u,adj[v]) {
			par[u] = v; depth[u] = depth[v]+1;
			dfsSz(u); sz[v] += sz[u];
			if (sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v = 1) {
		static int t = 0; pos[v] = t++; /// rpos.pb(v);
		trav(u,adj[v]) {
			root[u] = (u == adj[v][0] ? root[v] : u);
			dfsHld(u); }
	}
	void init(int _N) {
		N = _N; par[1] = depth[1] = 0; root[1] = 1; 
		dfsSz(); dfsHld(); }
	LazySeg<ll,SZ> tree;
	template <class BinaryOp>
	void processPath(int u, int v, BinaryOp op) {
		for (; root[u] != root[v]; v = par[root[v]]) {
			if (depth[root[u]] > depth[root[v]]) swap(u, v);
			op(pos[root[v]], pos[v]); }
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u]+VALS_IN_EDGES, pos[v]); 
	}
	void modifyPath(int u, int v, int val) { 
		processPath(u,v,[this, &val](int l,int r) { 
			tree.upd(l,r,val); }); }
	void modifySubtree(int v, int val) { 
		tree.upd(pos[v]+VALS_IN_EDGES,pos[v]+sz[v]-1,val); }
	ll queryPath(int u, int v) { 
		ll res = 0; processPath(u,v,[this,&res](int l,int r) { 
			res += tree.qsum(l,r); });
		return res; }
};
