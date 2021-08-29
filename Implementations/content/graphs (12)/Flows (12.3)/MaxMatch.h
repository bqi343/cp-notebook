/**
 * Description: Fast max matching.
 * Time: ?
 * Source: https://old.yosupo.jp/submission/48179
 * Verification: https://old.yosupo.jp/problem/bipartitematching
 */

vpi maxMatch(int L, int R, const vpi& edges) {
    V<vi> adj(L); each(e,edges) adj[e.f].pb(e.s);
    vi nxt(L,-1), pre(R,-1); vb vis;
    for (bool flag = 1; flag;) {
        flag = 0;
        auto dfs = [&](auto self, int x) {
            if (vis[x]) return 0;
            vis[x] = 1;
            for (int y: adj[x]) if (pre[y] == -1)
                return nxt[x] = y, pre[y] = x, 1;
            for (int y: adj[x]) if (self(self,pre[y]))
                return nxt[x] = y, pre[y] = x, 1;
            return 0;
        };
        vis = vb(L);
        F0R(i,L) if (nxt[i] == -1) flag |= dfs(dfs,i);
    }
    vpi ans; F0R(i,L) if (nxt[i] != -1) ans.eb(i,nxt[i]);
    return ans;
}