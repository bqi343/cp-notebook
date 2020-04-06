/**
 * Description: Used only once. Naive implementation of Misra \& Gries edge coloring. 
 * By Vizing's Theorem, a simple graph with max degree $d$ can be 
 * edge colored with at most $d+1$ colors 
 * Time: O(N^2M), faster in practice
 * Source: 
	* https://en.m.wikipedia.org/wiki/Vizing%27s_theorem 
	* https://en.wikipedia.org/wiki/Misra_%26_Gries_edge_coloring_algorithm
	* https://apps.dtic.mil/dtic/tr/fulltext/u2/a093097.pdf (optimal edge color on bipartite)
	* https://codeforces.com/blog/entry/62593
 * Verification: https://open.kattis.com/problems/gamescheduling
 */
 
template<int SZ> struct EdgeColor {
	int N = 0, maxDeg = 0, adj[SZ][SZ], deg[SZ];
	void init(int _N) { N = _N;
		F0R(i,N) { deg[i] = 0; F0R(j,N) adj[i][j] = 0; } }
	void ae(int a, int b, int c) { 
		adj[a][b] = adj[b][a] = c; }
	int delEdge(int a, int b) {
		int c = adj[a][b]; adj[a][b] = adj[b][a] = 0;
		return c; }
	vector<bool> genCol(int x) { 
		vector<bool> col(N+1); F0R(i,N) col[adj[x][i]] = 1;
		return col; }
	int freeCol(int u) {
		auto col = genCol(u); int x = 1; 
		while (col[x]) x ++; return x; }
	void invert(int x, int d, int c) {
		F0R(i,N) if (adj[x][i] == d) 
			delEdge(x,i), invert(i,c,d), ae(x,i,c); }
	void ae(int u, int v) { 
		// check if you can add edge w/o doing any work
		assert(N); ckmax(maxDeg,max(++deg[u],++deg[v]));
		auto a = genCol(u), b = genCol(v);
		FOR(i,1,maxDeg+2) if (!a[i] && !b[i]) 
			return ae(u,v,i); 
		/// 2. find maximal fan of u starting at v
		vector<bool> use(N); vi fan = {v}; use[v] = 1;
		while (1) {
			auto col = genCol(fan.bk);
			if (sz(fan) > 1) col[adj[fan.bk][u]] = 0;
			int i=0; while (i<N && (use[i] || col[adj[u][i]])) i++;
			if (i < N) fan.pb(i), use[i] = 1;
			else break;
		} 
		/// 3. choose free cols c and d for endpoints of fan
		/// 4. invert cd_u path
		int c = freeCol(u), d = freeCol(fan.bk); invert(u,d,c); 
		/// 5. find i such that d is free on fan[i]
		int i = 0; while (i < sz(fan) && genCol(fan[i])[d] 
			&& adj[u][fan[i]] != d) i ++; 
		assert (i != sz(fan));
		/// 6. rotate fan from 0 to i
		F0R(j,i) ae(u,fan[j],delEdge(u,fan[j+1]));
		/// 7. add new edge
		ae(u,fan[i],d);
	}
};
