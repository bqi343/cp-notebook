/**
 * Description: The centroid of a tree of size $N$ is a vertex such that 
 	* after removing it, all resulting subtrees have size at most $\frac{N}{2}.$ 
 	* Can support tree path queries and updates.
 * Time: O(N\log N)
 * Source: own
 * Verification: 
	* https://codeforces.com/contest/342/problem/E
	* Triway Cup 2019 G
 */

template<int SZ> struct Centroid {
	vi adj[SZ];
	bool done[SZ]; // processed as centroid yet
	int sub[SZ], par[SZ]; // subtree size, current par
	pi cen[SZ]; // immediate centroid anc
	vi dist[SZ]; // dists to all centroid ancs
	void ae(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
	void dfs(int x) {
		sub[x] = 1;
		trav(y,adj[x]) if (!done[y] && y != par[x]) {
			par[y] = x; dfs(y); sub[x] += sub[y]; }
	}
	int centroid(int x) {
		par[x] = -1; dfs(x); 
		for (int sz = sub[x];;) {
			pi mx = {0,0};
			trav(y,adj[x]) if (!done[y] && y != par[x]) 
				ckmax(mx,{sub[y],y});
			if (mx.f*2 <= sz) return x; 
			x = mx.s;
		}
	}
	void genDist(int x, int p) {
		dist[x].pb(dist[p].bk+1);
		trav(y,adj[x]) if (!done[y] && y != p) genDist(y,x); 
	} // CEN = {centroid above x, label of centroid subtree}
	void gen(pi CEN, int x) { 
		done[x = centroid(x)] = 1; cen[x] = CEN; 
		dist[x].pb(0); int co = 0;
		trav(y,adj[x]) if (!done[y]) genDist(y,x);
		trav(y,adj[x]) if (!done[y]) gen({x,co++},y);
	}
	void init() { gen({-1,0},1); } // start with vertex 1
};
