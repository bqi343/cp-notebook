/**
 * Description: O(N+M) Euler Path for both directed and undirected graphs
 * Source: USACO Training
 * Verification:
    * directed: https://open.kattis.com/problems/eulerianpath
    * undirected: USACO Training 3.3, Riding the Fences
 */

template<int SZ, bool directed> struct Euler {
    int N, M;
    vpi adj[SZ], circuit;
    int out[SZ], in[SZ], deg[SZ];
    bool bad;
    vector<bool> used;

    void clear() {
        FOR(i,1,N+1) adj[i].clear();
        circuit.clear(); used.clear();
        FOR(i,1,N+1) out[i] = in[i] = deg[i] = 0;
        N = M = bad = 0;
    }

    void dfs(int pre, int cur) {
        while (sz(adj[cur])) {
            pi x = adj[cur].back(); adj[cur].pop_back();
            if (used[x.s]) continue; // edge is already part of path
            used[x.s] = 1; dfs(cur,x.f);
        }
        if (sz(circuit) && circuit.back().f != cur) bad = 1;
        circuit.pb({pre,cur}); // generate circuit in reverse order
    }

    void addEdge(int a, int b) {
        if (directed) {
            adj[a].pb({b,M});
            out[a] ++, in[b] ++;
        } else {
            adj[a].pb({b,M}), adj[b].pb({a,M});
            deg[a] ++, deg[b] ++;
        }
        used.pb(0); M ++;
    }

    vi solve(int _N) { // vertices are 1-indexed
        N = _N;
        int start = 1; FOR(i,1,N+1) if (deg[i] || in[i] || out[i]) start = i;
        FOR(i,1,N+1)  {
            if (directed) {
                if (out[i]-in[i] == 1) start = i;
            } else {
                if (deg[i]&1) start = i;
            }
        }
        dfs(-1,start);
        if (sz(circuit) != M+1 || bad) return {}; // no sol
        vi ans; F0Rd(i,sz(circuit)) ans.pb(circuit[i].s);
        return ans;
    }
};