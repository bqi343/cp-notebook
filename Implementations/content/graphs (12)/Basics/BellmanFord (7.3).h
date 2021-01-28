/**
 * Description: Shortest Path w/ negative edge weights
    * Can be useful with linear programming
    * Constraints of the form x_i-x_j<k
 * Source: Own
 * Verification: 
    * https://open.kattis.com/problems/shortestpath3
    * https://probgate.org/viewproblem.php?pid=378
 */

template<int SZ> struct BellmanFord {
    int n;
    vi adj[SZ];
    vector<pair<pi,int>> ed;
    void ae(int u, int v, int w) { 
        adj[u].pb(v), ed.pb({{u,v},w}); }
    ll dist[SZ];
    void genBad(int x) { 
        // if x is reachable from negative cycle
        // -> update dists of all vertices which x can go to
        if (dist[x] == -INF) return;
        dist[x] = -INF; 
        each(t,adj[x]) genBad(t);
    }
    void init(int _n, int s) {
        n = _n; F0R(i,n) dist[i] = INF; 
        dist[s] = 0;
        F0R(i,n) each(a,ed) if (dist[a.f.f] < INF)
            ckmin(dist[a.f.s],dist[a.f.f]+a.s);
        each(a,ed) if (dist[a.f.f] < INF 
                    && dist[a.f.s] > dist[a.f.f]+a.s) 
            genBad(a.f.s);
    }
};
