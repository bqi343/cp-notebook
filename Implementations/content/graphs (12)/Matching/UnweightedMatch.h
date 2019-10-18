/**
 * Description: general unweighted matching
 * Time: ?
 * Source: 
	* https://github.com/koosaga/DeobureoMinkyuParty
	* https://www-m9.ma.tum.de/graph-algorithms/matchings-blossom-algorithm/index_en.html
 * Verification: https://codeforces.com/contest/1089/problem/B
 */

template<int SZ> struct UnweightedMatch {
	int vis[SZ], par[SZ], orig[SZ], match[SZ], aux[SZ], t, N; // 1-based index
	vi adj[SZ];
	queue<int> Q;
	void addEdge(int u, int v) {
		adj[u].pb(v); adj[v].pb(u);
	}
	
	void init(int n) {
		N = n; t = 0;
		F0R(i,N+1) {
			adj[i].clear();
			match[i] = aux[i] = par[i] = 0;
		}
	}
	
	void augment(int u, int v) {
		int pv = v, nv;
		do {
			pv = par[v]; nv = match[pv];
			match[v] = pv; match[pv] = v;
			v = nv;
		} while(u != pv);
	}
	
	int lca(int v, int w) {
		++t;
		while (1) {
			if (v) {
				if (aux[v] == t) return v; aux[v] = t;
				v = orig[par[match[v]]];
			}
			swap(v, w);
		}
	}
	
	void blossom(int v, int w, int a) {
		while (orig[v] != a) {
			par[v] = w; w = match[v];
			if (vis[w] == 1) Q.push(w), vis[w] = 0;
			orig[v] = orig[w] = a;
			v = par[w];
		}
	}
	
	bool bfs(int u) {
		fill(vis+1, vis+1+N, -1); iota(orig + 1, orig + N + 1, 1);
		Q = queue<int> (); Q.push(u); vis[u] = 0;
		while (sz(Q)) {
			int v = Q.front(); Q.pop();
			trav(x,adj[v]) {
				if (vis[x] == -1) {
					par[x] = v; vis[x] = 1;
					if (!match[x]) return augment(u, x), true;
					Q.push(match[x]); vis[match[x]] = 0;
				} else if (vis[x] == 0 && orig[v] != orig[x]) {
					int a = lca(orig[v], orig[x]);
					blossom(x, v, a); blossom(v, x, a);
				}
			}
		}
		return false;
	}
	
	int match() {
		int ans = 0;
		// find random matching (not necessary, constant improvement)
		vi V(N-1); iota(all(V), 1);
		shuffle(all(V), mt19937(0x94949));
		trav(x,V) if(!match[x]) 
			trav(y,adj[x]) if (!match[y]) {
				match[x] = y, match[y] = x;
				++ans; break;
			}
			
		FOR(i,1,N+1) if (!match[i] && bfs(i)) ++ans;
		return ans;
	}
};