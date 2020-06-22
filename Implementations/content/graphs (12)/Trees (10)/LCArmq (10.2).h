/**
 * Description: Euler Tour LCA. Compress takes a subset $S$ of nodes 
 	* and computes the minimal subtree that contains all the nodes 
	* pairwise LCA's and compressing edges. Returns a list of
	* \texttt{(par, orig\_index)} representing a tree rooted at 0. 
	* The root points to itself.
 * Time: O(N\log N) build, O(1) LCA
 * Source: USACO, Simon Lindholm (KACTL)
 * Verification: USACO Debug the Bugs
 	* https://codeforces.com/contest/1320/problem/E
 */

#include "../../data-structures/Static Range Queries (9.1)/RMQ (9.1).h"

struct LCA {
	int N; vector<vi> adj;
	vi depth, pos;
	vpi tmp; RMQ<pi> r;
	void init(int _N) { N = _N; adj.rsz(N); depth = pos = vi(N); }
	void ae(int x, int y) { adj[x].pb(y), adj[y].pb(x); }
	void dfs(int x, int p) {
		pos[x] = sz(tmp); tmp.eb(depth[x],x); 
		trav(y,adj[x]) if (y != p) {
			depth[y] = depth[x]+1;
			dfs(y,x), tmp.eb(depth[x],x);
		}
	}
	void gen(int R) { dfs(R,-1); r.init(tmp); }
	int lca(int u, int v){
		u = pos[u], v = pos[v]; if (u > v) swap(u,v);
		return r.query(u,v).s; }
	int dist(int u, int v) {
		return depth[u]+depth[v]-2*depth[lca(u,v)]; }
	vpi compress(vi S) {
		static vi rev; rev.rsz(N);
		auto cmp = [&](int a, int b) { return pos[a] < pos[b]; };
		sort(all(S),cmp); R0F(i,sz(S)-1) S.pb(lca(S[i],S[i+1]));
		sort(all(S),cmp); remDup(S);
		vpi ret{{0,S[0]}}; F0R(i,sz(S)) rev[S[i]] = i;
		F0R(i,sz(S)-1) ret.eb(rev[lca(S[i],S[i+1])],S[i+1]);
		return ret;
	}
};