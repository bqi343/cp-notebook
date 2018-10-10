/**
* Description: Shortest Path w/ negative edge weights 
    * Can be useful with linear programming
    * Constraints of the form x_i-x_j<k
* Verification: https://open.kattis.com/problems/shortestpath3
*/

int n,m,q,s,bad[1000];
vector<pair<pi,int>> edge;
ll dist[1000];

void solve() {
    edge.clear();
    F0R(i,n) dist[i] = INF, bad[i] = 0;
    dist[s] = 0;
    F0R(i,m) {
        int u,v,w; cin >> u >> v >> w;
        edge.pb({{u,v},w});
    }    
    F0R(i,n) for (auto a: edge) if (dist[a.f.f] < INF) dist[a.f.s] = min(dist[a.f.s], dist[a.f.f]+a.s); 
    for (auto a: edge) if (dist[a.f.f] < INF) if (dist[a.f.s] > dist[a.f.f]+a.s) bad[a.f.s] = 1;
    F0R(i,n) for (auto a: edge) if (bad[a.f.f]) bad[a.f.s] = 1;
    
    F0R(i,q) {
        int x; cin >> x;
        if (bad[x]) cout << "-Infinity\n";
        else if (dist[x] == INF) cout << "Impossible\n";
        else cout << dist[x] << "\n";
    }
    cout << "\n";
}
