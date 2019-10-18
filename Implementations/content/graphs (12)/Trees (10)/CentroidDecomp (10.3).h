/**
 * Description: can support tree path queries and updates
 * Time: $O(N\log N)$
 * Source: own
 * Verification: 
	* https://codeforces.com/contest/342/problem/E
	* Triway Cup 2019 G
 */

template<int SZ> struct CD {
	vi adj[SZ];
	bool done[SZ];
	int sub[SZ], par[SZ];
	vl dist[SZ];
	pi cen[SZ];
	void addEdge(int a, int b) { adj[a].pb(b), adj[b].pb(a); }

	void dfs (int x) {
		sub[x] = 1;
		trav(y,adj[x]) if (!done[y] && y != par[x]) {
			par[y] = x; dfs(y);
			sub[x] += sub[y];
		}
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
		dist[x].pb(dist[p].back()+1);
		trav(y,adj[x]) if (!done[y] && y != p) {
			cen[y] = cen[x];
			genDist(y,x);
		}
	}
	void gen(int x, bool fst = 0) {
		done[x = centroid(x)] = 1; dist[x].pb(0); 
		if (fst) cen[x].f = -1;
		int co = 0;
		trav(y,adj[x]) if (!done[y]) {
			cen[y] = {x,co++}; 
			genDist(y,x);
		}
		trav(y,adj[x]) if (!done[y]) gen(y);
	}
	void init() { gen(1,1); }
};