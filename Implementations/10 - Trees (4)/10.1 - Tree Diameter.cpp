/**
* Might not be obvious why this works!
* Verification: http://www.spoj.com/problems/PT07Z/
*/

int n, dist[MX], pre[MX];
vi adj[MX];

void dfs(int cur) {
    for (int i: adj[cur]) if (i != pre[cur]) {
        pre[i] = cur;
        dist[i] = dist[cur]+1;
        dfs(i);
    }
}

void genDist(int cur) {
    memset(dist,0,sizeof dist);
    pre[cur] = -1;
    dfs(cur);
}

int treeDiameter() {
    genDist(1);
    int bes = 0; FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i;
    genDist(bes); FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i;
    return dist[bes];
}

vi genCenter() {
    int t = treeDiameter();
    int bes = 0; FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i;
    
    F0R(i,t/2) bes = pre[bes];
    if (t&1) return {bes,pre[bes]};
    return {bes};
}

int main() {
    cin >> n;
    F0R(i,n-1) {
        int a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    vi x = genCenter();
    for (int i: x) cout << i << " ";
}
