/**
 * Description: Fast bipartite matching.
 * Time: $O(M\sqrt N)$
 * Source: Own
 * Verification: https://old.yosupo.jp/problem/bipartitenxting
 */

vpi maxMatch(int L, int R, const vpi& edges) {
	V<vi> adj = V<vi>(L);
	vi nxt(L,-1), prv(R,-1), lev, ptr;
	F0R(i,sz(edges)) adj.at(edges[i].f).pb(edges[i].s);
	while (true) {
		lev = ptr = vi(L); int max_lev = 0;
		queue<int> q; F0R(i,L) if (nxt[i]==-1) lev[i]=1, q.push(i);
		while (sz(q)) {
			int x = q.ft; q.pop();
			for (int y: adj[x]) {
				int z = prv[y];
				if (z == -1) max_lev = lev[x];
				else if (!lev[z]) lev[z] = lev[x]+1, q.push(z);
			}
			if (max_lev) break;
		}
		if (!max_lev) break;
		F0R(i,L) if (lev[i] > max_lev) lev[i] = 0;
		auto dfs = [&](auto self, int x) -> bool {
			for (;ptr[x] < sz(adj[x]);++ptr[x]) {
				int y = adj[x][ptr[x]], z = prv[y];
				if (z == -1 || (lev[z] == lev[x]+1 && self(self,z))) 
					return nxt[x]=y, prv[y]=x, ptr[x]=sz(adj[x]), 1;
			}
			return 0;
		};
		F0R(i,L) if (nxt[i] == -1) dfs(dfs,i);
	}
	vpi ans; F0R(i,L) if (nxt[i] != -1) ans.pb({i,nxt[i]});
	return ans;
}