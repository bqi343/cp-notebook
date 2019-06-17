/**
 * Description: Shortest Path w/ negative edge weights
    * Can be useful with linear programming
    * Constraints of the form x_i-x_j<k
 * Source: Own
 * Verification: https://open.kattis.com/problems/shortestpath3
 */

template<int SZ> struct BellmanFord {
    int n;
    vector<pair<pi,int>> ed;
    void addEdge(int u, int v, int w) { ed.pb({{u,v},w}); }
    
    bool bad[SZ];
    ll dist[SZ];
    ll getDist(int x) { return bad[x] ? -INF : dist[x]; }

    void init(int _n, int s) {
        n = _n;
        FOR(i,1,n+1) dist[i] = INF, bad[i] = 0;
        dist[s] = 0;

        F0R(i,n) trav(a,ed) if (dist[a.f.f] < INF)
            dist[a.f.s] = min(dist[a.f.s], dist[a.f.f]+a.s);

        trav(a,ed) if (dist[a.f.f] < INF)
            if (dist[a.f.s] > dist[a.f.f]+a.s) bad[a.f.s] = 1;

        F0R(i,n) trav(a,ed) if (bad[a.f.f]) bad[a.f.s] = 1;
    }
};
