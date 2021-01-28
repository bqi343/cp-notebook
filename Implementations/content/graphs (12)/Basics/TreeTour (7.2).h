/**
 * Description: Subtree corresponding to \texttt{x} -> range \texttt{[st[x],en[x]]}
 * Source: Own
 */

template<int SZ> struct TreeTour {
	int st[SZ], en[SZ], par[SZ];
	vi adj[SZ];
	void ae(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
	void dfs(int x) {
		static int t = 0; st[x] = t++;
		each(y,adj[x]) if (y != par[x]) {
			par[y] = x; dfs(y); }
		en[x] = t-1;
	}	
	void init() { par[1] = 0; dfs(1); }
};

void tourExample() {
	TreeTour<4> T;
	T.ae(1,2); T.ae(1,3); T.init();
	FOR(i,1,4) ps(i,T.st[i],T.en[i]); 
	// 1 0 2, 2 1 1, 3 2 2
}
