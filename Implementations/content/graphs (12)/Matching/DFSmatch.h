/**
 * Description: naive bipartite matching
 * Time: O(NM)
 * Source: own
 * Verification: USACO Training unmatch
 */

template<int SZ> struct MaxMatch {
	int N, match[SZ], rmatch[SZ];
	bitset<SZ> vis; vi adj[SZ];
	/**void connect(int a, int b, bool c = 1) {
		if (c) match[a] = b, rmatch[b] = a;
		else match[a] = rmatch[b] = 0; }*/
	bool dfs(int x) {
		if (!x) return 1;
		if (vis[x]) return 0;
		vis[x] = 1;
		each(t,adj[x]) if (t != match[x] && dfs(rmatch[t])) {
			match[x] = t, rmatch[t] = x; return 1; }
		return 0;
	}
	bool tri(int x) { vis.reset(); return dfs(x); }
	int init(int _N) { 
		N = _N; FOR(i,1,N+1) match[i] = rmatch[i] = 0;
		int res = 0; FOR(i,1,N+1) if (!match[i]) res += tri(i); 
		return res;
	}
};
