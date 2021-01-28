/**
 * Description: Three-Edge-Connected Components
 * Time: O(N+M) (+ DSU constant that can be removed)
 * Source: https://judge.yosupo.jp/submission/5244
 * Verification: https://judge.yosupo.jp/problem/three_edge_connected_components
 */

template<int SZ> struct ThreeEdgeCC {
	vi adj[SZ]; DSU D;
	void ae(int a, int b) { if (a != b) adj[a].pb(b), adj[b].pb(a); } // no self-loops
	int ti,in[SZ],out[SZ],deg[SZ],low[SZ],path[SZ];
	void dfs(int v, int p) { // deg -> # of back-edges that cross parent edge
		in[v] = ++ti; 
		auto absorb = [&](int a, int b) { // join into same 3CC
			assert(D.unite(a,b)); deg[a] += deg[b]; };
		each(w,adj[v]) {
			if (w == p) { p = -1; continue; } // ignore first parent edge
			if (in[w]) { // visited
				if (in[w] < in[v]) deg[v] ++, ckmin(low[v],in[w]); // above v
				else {
					deg[v] --; int& u = path[v];
					for (;u!=-1&&in[u]<=in[w]&&in[w]<=out[u]; u=path[u])
						absorb(v,u); // paths from v to u, u to w, edge from w to v
				}
				continue;
			}
			dfs(w,v);
			if (path[w] == -1 && deg[w] <= 1) { // <= 1 back-edge goes over w?
				deg[v] += deg[w], ckmin(low[v],low[w]);
				continue; }
			if (!deg[w]) w = path[w];
			if (ckmin(low[v],low[w])) swap(w,path[v]);
			for (;w != -1; w = path[w]) absorb(v,w);
		}
		out[v] = ti;
	}
	vector<vi> calc(int N) {
		D.init(N); ti = 0;
		F0R(i,N) {
			in[i] = out[i] = deg[i] = 0;
			low[i] = MOD; path[i] = -1;
		}
		F0R(i,N) if (!in[i]) dfs(i,-1);
		vi res[N]; F0R(i,N) res[D.get(i)].pb(i);
		vector<vi> ans; F0R(i,N) if (sz(res[i])) ans.pb(res[i]);
		return ans;
	}
};
