/**
 * Description: Faster Flow, Bipartite Matching
 * Source: GeeksForGeeks
 * Verification: RMI 2017 Day 1 Fashion
    * https://pastebin.com/VJxTvEg1
 */

typedef ll F; // flow type
struct Edge { int v, rev; F f, c; };

template<int SZ> struct Dinic {
    vector<Edge> adj[SZ];
    vector<Edge>::iterator cur[SZ];
    void addEdge(int u, int v, F cap, F rcap = 0) {
        assert(min(cap,rcap) >= 0); // don't try smth dumb
        Edge a{v, sz(adj[v]), 0, cap}, b{u, sz(adj[u]), 0, rcap};
        adj[u].pb(a), adj[v].pb(b);
    }

    int N, st, en;
    int level[SZ];
    bool bfs() { // level = shortest distance from source
        // after computing flow, edges {u,v} such that level[u] \neq -1, level[v] = -1 are part of min cut
        FOR(i,1,N+1) level[i] = -1, cur[i] = begin(adj[i]);
        queue<int> q; level[st] = 0; q.push(st);
        while (sz(q)) {
            int u = q.front(); q.pop();
            trav(e,adj[u]) if (level[e.v] < 0 && e.f < e.c) {
                level[e.v] = level[u]+1; q.push(e.v);
            }
        }
        return level[en] >= 0;
    }

    F sendFlow(int s, F flow) {
        if (s == en) return flow;
        for (; cur[s] != end(adj[s]); cur[s]++) {
            Edge& e = *cur[s];
            if (level[e.v] != level[s]+1 || e.f == e.c) continue;
            auto f = sendFlow(e.v, min(flow, e.c-e.f));
            if (f) { // saturated at least one edge
                e.f += f; adj[e.v][e.rev].f -= f;
                return f;
            }
        }
        return 0;
    }
    F maxFlow(int _N, int _st, int _en) {
        N = _N; st = _st, en = _en; if (st == en) return -1;
        F tot = 0;
        while (bfs()) while (auto flow = sendFlow(st, LLONG_MAX)) tot += flow;
        return tot;
    }
};

