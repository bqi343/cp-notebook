/**
 * Description: Max matching that seems to be fast (probably a counter case ...)
 * Time: ?
 * Source: https://old.yosupo.jp/submission/48179
 * Verification: https://old.yosupo.jp/problem/bipartitematching
 */

vpi maxMatch(int L, int R, const vpi& edges) {
    V<vi> adj(L); each(e,edges) adj[e.f].pb(e.s);
    vi nxt(L,-1), prv(R,-1); vb vis;
    for (bool flag = 1; flag;) {
        flag = 0;
        auto dfs = [&](auto self, int x) {
            if (vis[x]) return 0;
            vis[x] = 1;
            for (int y: adj[x]) if (prv[y] == -1)
                return nxt[x] = y, prv[y] = x, 1;
            for (int y: adj[x]) if (self(self,prv[y]))
                return nxt[x] = y, prv[y] = x, 1;
            return 0;
        };
        vis = vb(L);
        F0R(i,L) if (nxt[i] == -1) flag |= dfs(dfs,i);
    }
    vpi ans; F0R(i,L) if (nxt[i] != -1) ans.eb(i,nxt[i]);
    return ans;
}