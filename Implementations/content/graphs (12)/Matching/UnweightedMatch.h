/**
 * Description: Edmond's Blossom Algorithm. General unweighted 
 	* matching with 1-based indexing. If \texttt{vis[v]=0}
 	* when \texttt{bfs} returns 0, \texttt{v} is not part of every 
 	* max matching.
 * Time: O(N^3), faster in practice
 * Source: 
	* https://github.com/koosaga/DeobureoMinkyuParty
	* https://www-m9.ma.tum.de/graph-algorithms/matchings-blossom-algorithm/index_en.html
	* https://codeforces.com/blog/entry/63630
 * Verification: 
 	* https://codeforces.com/contest/1089 B
 	* https://www.codechef.com/problems/HAMILG
 */

template<int SZ> struct UnweightedMatch {
	int match[SZ], N; vi adj[SZ];
	void ae(int u, int v) { adj[u].pb(v), adj[v].pb(u); }
	queue<int> q;
	int par[SZ], vis[SZ], orig[SZ], aux[SZ];
	void augment(int u, int v) { // toggle edges on u-v path
		while (1) { // one more matched pair
			int pv = par[v], nv = match[pv];
			match[v] = pv; match[pv] = v;
			v = nv; if (u == pv) return;
		}
	}
	int lca(int u, int v) { // find LCA of supernodes in O(dist)
		static int t = 0;
		for (++t;;swap(u,v)) {
			if (!u) continue;
			if (aux[u] == t) return u; // found LCA
			aux[u] = t; u = orig[par[match[u]]];
		}
	}
	void blossom(int u, int v, int a) { // go other way
		for (; orig[u] != a; u = par[v]) { // around cycle
			par[u] = v; v = match[u]; // treat u as if vis[u] = 1
			if (vis[v] == 1) vis[v] = 0, q.push(v);
			orig[u] = orig[v] = a; // merge into supernode
		}
	}
	bool bfs(int u) { // u is initially unmatched
		F0R(i,N+1) par[i] = 0, vis[i] = -1, orig[i] = i;
		q = queue<int>(); vis[u] = 0, q.push(u);
		while (sz(q)) { // each node is pushed to q at most once
			int v = q.ft; q.pop(); // 0 -> unmatched vertex
			each(x,adj[v]) {
				if (vis[x] == -1) { // neither of x, match[x] visited
					vis[x] = 1; par[x] = v;
					if (!match[x]) return augment(u,x),1;
					vis[match[x]] = 0, q.push(match[x]);
				} else if (vis[x] == 0 && orig[v] != orig[x]) {
					int a = lca(orig[v],orig[x]); // odd cycle
					blossom(x,v,a), blossom(v,x,a); 
				} // contract O(n) times
			}
		}
		return 0;
	}
	int calc(int _N) { // rand matching -> constant improvement
		N = _N; F0R(i,N+1) match[i] = aux[i] = 0; 
		int ans = 0; vi V(N); iota(all(V),1); shuffle(all(V),rng); // find rand matching
		each(x,V) if (!match[x]) each(y,adj[x]) if (!match[y]) { 
			match[x] = y, match[y] = x; ++ans; break; }
		FOR(i,1,N+1) if (!match[i] && bfs(i)) ++ans;
		return ans;
	}
};
