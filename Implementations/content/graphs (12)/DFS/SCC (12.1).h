/**
 * Description: Kosaraju's Algorithm, DFS two times to generate 
 	* strongly connected components in topological order. $a,b$
 	* in same component if both $a\to b$ and $b\to a$ exist.
 * Time: O(N+M)
 * Source: Wikipedia
 * Verification: POI 8 peaceful commission
 */

template<int SZ> struct SCC {
	int N, comp[SZ];
	vi adj[SZ], radj[SZ], todo, allComp;
	bitset<SZ> vis;
	void ae(int a, int b) { adj[a].pb(b), radj[b].pb(a); }
	void dfs(int v) {
		vis[v] = 1; trav(w,adj[v]) if (!vis[w]) dfs(w);
		todo.pb(v); }
	void dfs2(int v, int val) {
		comp[v] = val; 
		trav(w,radj[v]) if (comp[w] == -1) dfs2(w,val); }
	void init(int _N) { // fills allComp
		N = _N; F0R(i,N) comp[i] = -1, vis[i] = 0;
		F0R(i,N) if (!vis[i]) dfs(i);
		reverse(all(todo)); 
		trav(i,todo) if (comp[i] == -1) dfs2(i,i), allComp.pb(i);
	}
};
