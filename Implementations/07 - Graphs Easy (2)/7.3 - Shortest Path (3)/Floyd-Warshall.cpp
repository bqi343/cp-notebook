/**
* Description: All-Pairs Shortest Path
* Source: Own
* Verification: https://open.kattis.com/problems/allpairspath
*/

template<int SZ> struct FloydWarshall {
    int n; // vertices, edges, queries
    ll dist[SZ][SZ];
    bool bad[SZ][SZ];

    ll query(int x, int y) {
        if (bad[x][y]) return -INF;
        return dist[x][y];
    }

    void solve() {
        F0R(i,n) F0R(j,n) dist[i][j] = INF, bad[i][j] = 0;
        F0R(i,n) dist[i][i] = 0;
        F0R(i,m) {
            int u,v,w; cin >> u >> v >> w;
            dist[u][v] = min(dist[u][v],(ll)w);
        }

        F0R(k,n) F0R(i,n) F0R(j,n) if (dist[i][k] != INF && dist[k][j] != INF) 
            dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
        
        F0R(k,n) F0R(i,n) F0R(j,n) if (dist[i][k] != INF && dist[k][j] != INF)  
            if (dist[i][j] > dist[i][k]+dist[k][j])
                bad[i][j] = 1;
                
        F0R(k,n) F0R(i,n) F0R(j,n) {
            if (dist[i][k] < INF && bad[k][j]) bad[i][j] = 1;
            if (bad[i][k] && dist[k][j] < INF) bad[i][j] = 1;
        }
    }
};