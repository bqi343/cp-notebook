/**
 * Description: Faster Flow, Bipartite Matching
 * Source: GeeksForGeeks
 * Verification: RMI 2017 Day 1 Fashion
    * https://pastebin.com/VJxTvEg1
 */

template<int SZ> struct Dinic {
    typedef ll F; // flow type
    struct Edge { int to, rev; F f, c; };
    
    int N,s,t;
    vector<Edge> adj[SZ];
    typename vector<Edge>::iterator cur[SZ];
    void addEdge(int u, int v, F cap) {
        assert(cap >= 0); // don't try smth dumb
        Edge a{v, sz(adj[v]), 0, cap}, b{u, sz(adj[u]), 0, 0};
        adj[u].pb(a), adj[v].pb(b);
    }

    int level[SZ];
    bool bfs() { // level = shortest distance from source
        // after computing flow, edges {u,v} such that level[u] \neq -1, level[v] = -1 are part of min cut
        F0R(i,N) level[i] = -1, cur[i] = begin(adj[i]);
        queue<int> q({s}); level[s] = 0; 
        while (sz(q)) {
            int u = q.front(); q.pop();
            trav(e,adj[u]) if (level[e.to] < 0 && e.f < e.c) {
                level[e.to] = level[u]+1; q.push(e.to);
            }
        }
        return level[t] >= 0;
    }

    F sendFlow(int v, F flow) {
        if (v == t) return flow;
        for (; cur[v] != end(adj[v]); cur[v]++) {
            Edge& e = *cur[v];
            if (level[e.to] != level[v]+1 || e.f == e.c) continue;
            auto df = sendFlow(e.to,min(flow,e.c-e.f));
            if (df) { // saturated at least one edge
                e.f += df; adj[e.to][e.rev].f -= df;
                return df;
            }
        }
        return 0;
    }
    F maxFlow(int _N, int _s, int _t) {
        N = _N, s = _s, t = _t; if (s == t) return -1;
        F tot = 0;
        while (bfs()) while (auto flow = sendFlow(s,numeric_limits<F>::max())) tot += flow;
        return tot;
    }
};