/**
 * Description: naive implementation of Misra \& Gries edge coloring, 
 * by Vizing's Theorem a simple graph with max degree $d$ can be 
 * edge colored with at most $d+1$ colors 
 * Time: O(MN^2)
 * Source: 
	* https://en.m.wikipedia.org/wiki/Vizing%27s_theorem 
	* https://en.wikipedia.org/wiki/Misra_%26_Gries_edge_coloring_algorithm
 * Verification: https://open.kattis.com/problems/gamescheduling
 */
 
template<int SZ> struct EdgeColor {
	int N = 0, maxDeg = 0, adj[SZ][SZ], deg[SZ];
	EdgeColor() { 
		memset(adj,0,sizeof adj); 
		memset(deg,0,sizeof deg);
	}
	void addEdge(int a, int b, int c) { 
		adj[a][b] = adj[b][a] = c; 
	}
	int delEdge(int a, int b) {
		int c = adj[a][b]; 
		adj[a][b] = adj[b][a] = 0;
		return c;
	}
	vector<bool> genCol(int x) { 
		vector<bool> col(N+1); F0R(i,N) col[adj[x][i]] = 1;
		return col;
	}
	int freeCol(int u) {
		auto col = genCol(u);
		int x = 1; while (col[x]) x ++; return x;
	}
	void invert(int x, int d, int c) {
		F0R(i,N) if (adj[x][i] == d) 
			delEdge(x,i), invert(i,c,d), addEdge(x,i,c);
	}
	void addEdge(int u, int v) { // follows wikipedia steps
		// check if you can add edge w/o doing any work
		assert(N); ckmax(maxDeg,max(++deg[u],++deg[v]));
		auto a = genCol(u), b = genCol(v);
		FOR(i,1,maxDeg+2) if (!a[i] && !b[i]) return addEdge(u,v,i); 

		// 2. find maximal fan of u starting at v
		vector<bool> use(N); vi fan = {v}; use[v] = 1;
		while (1) {
			auto col = genCol(fan.back());
			if (sz(fan) > 1) col[adj[fan.back()][u]] = 0;
			int i = 0; while (i < N && (use[i] || col[adj[u][i]])) i ++;
			if (i < N) fan.pb(i), use[i] = 1;
			else break;
		} 

		// 3/4. choose free cols for endpoints of fan, invert cd_u path
		int c = freeCol(u), d = freeCol(fan.back()); invert(u,d,c); 
		// 5. find i such that d is free on fan[i]
		int i = 0; while (i < sz(fan) && genCol(fan[i])[d] 
			&& adj[u][fan[i]] != d) i ++; 
		assert (i != sz(fan));
		// 6. rotate fan from 0 to i
		F0R(j,i) addEdge(u,fan[j],delEdge(u,fan[j+1]));
		// 7. add new edge
		addEdge(u,fan[i],d);
	}
};