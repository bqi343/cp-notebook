/**
 * Description: All-Pairs Shortest Path
 * Source: Own
 * Verification: 
    * https://open.kattis.com/problems/allpairspath
    * https://cses.fi/problemset/task/1672/
 */

template<int SZ> struct FloydWarshall {
    int n; 
    vector<pair<pi,int>> ed;
    void addEdge(int u, int v, int w) { ed.pb({{u,v},w}); }

    ll dist[SZ][SZ];
    bool bad[SZ][SZ];
    ll getDist(int x, int y) { return bad[x][y] ? -INF : dist[x][y]; }

    void init(int _n) {
        n = _n;
        FOR(i,1,n+1) FOR(j,1,n+1) dist[i][j] = INF, bad[i][j] = 0;
        FOR(i,1,n+1) dist[i][i] = 0;
        trav(t,ed) ckmin(dist[t.f.f][t.f.s],(ll)t.s);

        FOR(k,1,n+1) FOR(i,1,n+1) FOR(j,1,n+1) if (dist[i][k] != INF && dist[k][j] != INF) 
            ckmin(dist[i][j],dist[i][k]+dist[k][j]);
        
        FOR(k,1,n+1) FOR(i,1,n+1) FOR(j,1,n+1) if (dist[i][k] != INF && dist[k][j] != INF)  
            if (dist[i][j] > dist[i][k]+dist[k][j]) bad[i][j] = 1;
                
        FOR(k,1,n+1) FOR(i,1,n+1) FOR(j,1,n+1) {
            if (dist[i][k] < INF && bad[k][j]) bad[i][j] = 1;
            if (bad[i][k] && dist[k][j] < INF) bad[i][j] = 1;
        }
    }
};