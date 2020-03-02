/**
 * Description: Euler Tour LCA w/ O(1) query. Compress takes a subset $S$ 
 	* of nodes and computes the minimal subtree that contains all the nodes 
	* pairwise LCA's and compressing edges. Returns a list of (par, orig\_index) 
	* representing a tree rooted at 0. The root points to itself.
 * Source: USACO, Simon Lindholm (KACTL)
 * Verification: USACO Debug the Bugs
 	* https://codeforces.com/contest/1320/problem/E
 */

#include "../../data-structures/Static Range Queries (9.1)/RMQ (9.1).h"

template<int SZ> struct LCA {
	int N, R = 1, depth[SZ], st[SZ];
	vi adj[SZ]; vpi tmp; RMQ<pi> r;
	void ae(int u, int v) { adj[u].pb(v), adj[v].pb(u); }
	void dfs(int u, int prev){
		st[u] = sz(tmp), depth[u] = depth[prev]+1;
		tmp.pb({depth[u],u});
		trav(v,adj[u]) if (v != prev) 
			dfs(v,u), tmp.pb({depth[u],u});
	}
	void init(int _N) { N = _N; dfs(R,0); r.init(tmp); }
	int lca(int u, int v){
		u = st[u], v = st[v]; if (u > v) swap(u,v);
		return r.query(u,v).s; }
	/// int dist(int u, int v) {
		/// return depth[u]+depth[v]-2*depth[lca(u,v)]; }
	vpi compress(vi S) {
		static vi rev; rev.rsz(N+1);
		auto cmp = [&](int a, int b) { return st[a] < st[b]; };
		sort(all(S),cmp);
		int m = sz(S)-1; F0R(i,m) S.pb(lca(S[i],S[i+1]));
		sort(all(S),cmp); S.erase(unique(all(S)),end(S));
		F0R(i,sz(S)) rev[S[i]] = i;
		vpi ret = {pi(0,S[0])};
		F0R(i,sz(S)-1) ret.eb(rev[lca(S[i],S[i+1])],S[i+1]);
		return ret;
	}
};