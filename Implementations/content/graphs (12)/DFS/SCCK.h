/**
 * Description: Kosaraju's Algorithm, DFS twice to generate 
 	* strongly connected components in topological order. $a,b$
 	* in same component if both $a\to b$ and $b\to a$ exist.
 * Time: O(N+M)
 * Source: Wikipedia
 * Verification: POI 8 peaceful commission
 */

struct SCC {
	int N; vector<vi> adj, radj;
	vi todo, comp, comps; vector<bool> vis;
	void init(int _N) { N = _N; 
		adj.rsz(N), radj.rsz(N), comp = vi(N,-1), vis.rsz(N); }
	void ae(int x, int y) { adj[x].pb(y), radj[y].pb(x); }
	void dfs(int x) {
		vis[x] = 1; each(y,adj[x]) if (!vis[y]) dfs(y);
		todo.pb(x); }
	void dfs2(int x, int v) {
		comp[x] = v; 
		each(y,radj[x]) if (comp[y] == -1) dfs2(y,v); }
	void gen() { // fills allComp
		F0R(i,N) if (!vis[i]) dfs(i);
		reverse(all(todo)); 
		each(x,todo) if (comp[x] == -1) dfs2(x,x), comps.pb(x);
	}
};
