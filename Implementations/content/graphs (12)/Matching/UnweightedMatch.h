/**
 * Description: Edmond's Blossom Algorithm. 
 	* General unweighted matching with 1-based indexing.
 * Time: O(N^2M)
 * Source: 
	* https://github.com/koosaga/DeobureoMinkyuParty
	* https://www-m9.ma.tum.de/graph-algorithms/matchings-blossom-algorithm/index_en.html
 * Verification: https://codeforces.com/contest/1089/problem/B
 */

template<int SZ> struct UnweightedMatch {
	int match[SZ], N; vi adj[SZ];
	void ae(int u, int v) { adj[u].pb(v), adj[v].pb(u); }
	void init(int _N) { N = _N; 
		FOR(i,1,N+1) adj[i].clear(), match[i] = 0; }
	queue<int> Q;
	int par[SZ], vis[SZ], orig[SZ], aux[SZ]; 
	void augment(int u, int v) { // toggle edges on u-v path
		int pv = v, nv;
		do {
			pv = par[v]; nv = match[pv];
			match[v] = pv; match[pv] = v;
			v = nv;
		} while (u != pv);
	}
	int lca(int v, int w) { // find LCA in O(dist)
		static int tt = 0; ++tt;
		while (1) {
			if (v) {
				if (aux[v] == tt) return v; 
				aux[v] = tt; v = orig[par[match[v]]];
			}
			swap(v,w);
		}
	}
	void blossom(int v, int w, int a) {
		while (orig[v] != a) {
			par[v] = w; w = match[v]; // go other way around cycle
			if (vis[w] == 1) Q.push(w), vis[w] = 0;
			orig[v] = orig[w] = a; // merge into supernode
			v = par[w];
		}
	}
	bool bfs(int u) {
		F0R(i,N+1) par[i] = aux[i] = 0, vis[i] = -1, orig[i] = i;
		Q = queue<int>(); Q.push(u); vis[u] = 0;
		while (sz(Q)) {
			int v = Q.ft; Q.pop();
			trav(x,adj[v]) {
				if (vis[x] == -1) {
					par[x] = v; vis[x] = 1;
					if (!match[x]) return augment(u,x),1;
					Q.push(match[x]); vis[match[x]] = 0;
				} else if (vis[x] == 0 && orig[v] != orig[x]) { 
					int a = lca(orig[v], orig[x]); // odd cycle
					blossom(x,v,a); blossom(v,x,a);
				}
			}
		}
		return 0;
	}
	int calc() {
		int ans = 0; // find random matching, constant improvement
		vi V(N-1); iota(all(V),1); shuffle(all(V),rng);
		trav(x,V) if (!match[x]) trav(y,adj[x]) if (!match[y]) 
			{ match[x] = y, match[y] = x; ++ans; break; }
		FOR(i,1,N+1) if (!match[i] && bfs(i)) ++ans;
		return ans;
	}
};