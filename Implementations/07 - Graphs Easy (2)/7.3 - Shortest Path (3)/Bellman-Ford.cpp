/**
 * Description: Shortest Path w/ negative edge weights
    * Can be useful with linear programming
    * Constraints of the form x_i-x_j<k
 * Source: Own
 * Verification: https://open.kattis.com/problems/shortestpath3
 */

template<int SZ> struct BellmanFord {
    int n;
    bool bad[SZ];
    vector<pair<pi,int>> edge;
    ll dist[SZ];

    ll query(int x) { // get distance to node x
        if (bad[x]) return -INF;
        return dist[x];
    }

    void init(int s) {
        F0R(i,n) dist[i] = INF, bad[i] = 0;
        dist[s] = 0;

        F0R(i,n) trav(a,edge) if (dist[a.f.f] < INF)
            dist[a.f.s] = min(dist[a.f.s], dist[a.f.f]+a.s);

        trav(a,edge) if (dist[a.f.f] < INF)
            if (dist[a.f.s] > dist[a.f.f]+a.s) bad[a.f.s] = 1;

        F0R(i,n) trav(a,edge) if (bad[a.f.f]) bad[a.f.s] = 1;
    }
};
