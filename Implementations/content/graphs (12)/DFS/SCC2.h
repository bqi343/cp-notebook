/**
 * Description: Tarjan's Algorithm, DFS two times to generate 
 	* strongly connected components in topological order. $a,b$
 	* in same component if both $a\to b$ and $b\to a$ exist.
 	* Uses less memory than Kosaraju b/c no need to store reverse edges.
 * Time: O(N+M)
 * Source: KACTL
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/SCC.h
 * Verification: https://cses.fi/problemset/task/1686/
 */

 template<int SZ> struct SCC {
	vi adj[SZ], allComp, st; 	
	int N, val[SZ], comp[SZ];
	void ae(int u, int v) { adj[u].pb(v); }
	int dfs(int u) {
		static int t = 0; int low = val[u] = ++t; st.pb(u);
		trav(i,adj[u]) if (comp[i] < 0) ckmin(low,val[i]?:dfs(i));
		if (low == val[u]) {
			allComp.pb(u); int x; 
			do { comp[x=st.bk] = u; st.pop_back(); } while (x!=u);
		}
		return val[u] = low;
	}
	void init(int _N) {
		N = _N; F0R(i,N) val[i] = 0, comp[i] = -1;
		F0R(i,N) if (comp[i] < 0) dfs(i);
		reverse(all(allComp));
	}
};