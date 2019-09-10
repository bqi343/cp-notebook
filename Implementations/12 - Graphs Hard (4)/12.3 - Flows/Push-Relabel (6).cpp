/**
 * Description: Push-Relabel
 * Source: KACTL
 * Verification: https://www.spoj.com/problems/FASTFLOW/
 	* https://open.kattis.com/problems/maxflow
 */

typedef ll F; // flow type
struct Edge { int v, rev; F f, c; };

template<int SZ> struct PushRelabel {
    vector<Edge> adj[SZ];
    vector<Edge>::iterator cur[SZ];
    void addEdge(int u, int v, F cap, F rcap = 0) {
        assert(min(cap,rcap) >= 0); // don't try smth dumb
        Edge a{v, sz(adj[v]), 0, cap}, b{u, sz(adj[u]), 0, rcap};
        adj[u].pb(a), adj[v].pb(b);
    }

    F ec[SZ];
    int H[SZ], co[SZ];
    vi hs[2*SZ]; // highest label selection

    void addFlow(Edge& e, F f) {
        Edge& back = adj[e.v][e.rev];
        if (!ec[e.v] && f) hs[H[e.v]].push_back(e.v);
        e.f += f; e.c -= f; ec[e.v] += f;
        back.f -= f; back.c += f; ec[back.v] -= f;
    }
    
    F maxFlow(int N, int st, int en) {
        FOR(i,1,N+1) ec[i] = H[i] = 0;
        F0R(i,N) co[i] = 0;
        co[0] = N-1; H[st] = N; ec[en] = 1; 
        FOR(i,1,N+1) cur[i] = begin(adj[i]);
        trav(e, adj[st]) addFlow(e, e.c);

        for (int hi = 0;;) {
            while (!sz(hs[hi])) if (!hi--) return -ec[st]; // if all flow returns back to source then 0
            int u = hs[hi].back(); hs[hi].pop_back(); // select node with highest label to discharge
            while (ec[u])  // discharge u
                if (cur[u] == end(adj[u])) {
                    H[u] = 1e9;
                    for (auto it = begin(adj[u]); it != end(adj[u]); it++) {
                        Edge& e = *it;
                        if (e.c && H[u] > H[e.v]+1) 
                            H[u] = H[e.v]+1, cur[u] = it;
                    }
                    if (H[u] < N) co[H[u]] ++;
                    if (hi < N && !--co[hi]) 
                        FOR(i,1,N+1) if (hi < H[i] && H[i] < N) // gap heuristic -> kill all these nodes
                            --co[H[i]], H[i] = N+1;
                    hi = H[u]; 
                } else if (cur[u]->c && H[u] == H[cur[u]->v]+1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else cur[u]++;
        }
    }
};