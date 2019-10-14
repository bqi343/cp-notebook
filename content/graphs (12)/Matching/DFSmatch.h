/**
 * Description: naive bipartite matching
 * Time: O(NM)
 * Source: own
 * Verification: USACO Training unmatch
 */

template<int SZ> struct MaxMatch {
	int N, flow = 0, match[SZ], rmatch[SZ];
	bitset<SZ> vis;
	vi adj[SZ];
	MaxMatch() { 
		memset(match,0,sizeof match); 
		memset(rmatch,0,sizeof rmatch); 
	}
	
	void connect(int a, int b, bool c = 1) {
		if (c) match[a] = b, rmatch[b] = a;
		else match[a] = rmatch[b] = 0;
	}
	bool dfs(int x) {
		if (!x) return 1;
		if (vis[x]) return 0;
		vis[x] = 1;
		trav(t,adj[x]) if (t != match[x] && dfs(rmatch[t])) 
			return connect(x,t),1;
		return 0;
	}
	void tri(int x) { vis.reset(); flow += dfs(x); }
	void init(int _N) { 
		N = _N; FOR(i,1,N+1) if (!match[i]) tri(i); 
	}
};