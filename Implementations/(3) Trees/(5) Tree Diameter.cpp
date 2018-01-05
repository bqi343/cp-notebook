/**
* Might not be obvious why this works!
* Verification: http://www.spoj.com/problems/PT07Z/
*/

const int MX = 10001;

int n, dist[MX];
vi adj[MX];

void dfs(int cur, int pre) {
    for (int i: adj[cur]) if (i != pre) {
        dist[i] = dist[cur]+1;
        dfs(i,cur);
    }
}

void dfs(int cur) {
    memset(dist,0,sizeof dist);
    dfs(cur,-1);
}

int treeDiameter() {
    dfs(1);
    int bes = 0; FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i;
    dfs(bes); FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i;
    return dist[bes];
}

int main() {
    cin >> n;
    F0R(i,n-1) {
        int a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    cout << treeDiameter();
}
