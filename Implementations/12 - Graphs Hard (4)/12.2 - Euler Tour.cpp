/**
 * Description: O(N+M) euler tour for both directed and undirected graphs
 * Source: USACO Training
 * Verification:
    * directed: https://open.kattis.com/problems/eulerianpath
    * undirected: USACO Training 3.3, Riding the Fences
 */

template<int SZ, bool directed> struct Euler {
    int N, M;
    vpi adj[SZ], circuit;
    int out[SZ], in[SZ], deg[SZ];
    bool used[SZ], bad;

    void clr() {
        F0R(i,N) adj[i].clear();
        circuit.clear();
        F0R(i,N) out[i] = in[i] = deg[i] = 0;
        F0R(i,M) used[i] = 0;
        N = M = bad = 0;
    }

    void dfs(int pre, int cur) {
        while (sz(adj[cur])) {
            pi x = adj[cur].back(); adj[cur].pop_back();
            if (used[x.s]) continue;
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
        M ++;
    }

    vi solve(int _N) {
        N = _N; // edges only involve vertices from 0 to N-1

        int start = 0; F0R(i,N) if (deg[i] || in[i] || out[i]) start = i;
        if (directed) {
            F0R(i,N) if (out[i]-in[i] == 1) start = i;
        } else {
            F0R(i,N) if (deg[i]&1) start = i;
        }
        dfs(-1,start);

        if (sz(circuit) != M+1 || bad) return {}; // return empty if no sol
        vi ans; F0Rd(i,sz(circuit)) ans.pb(circuit[i].s);
        return ans;
    }
};
