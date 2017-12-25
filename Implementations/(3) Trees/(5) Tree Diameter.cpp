/**
* Usage: CF Brain Network
* Might not be obvious why this works!
*/

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
    dfs(0);
    int bes = 0; F0R(i,n) if (dist[i] > dist[bes]) bes = i;
    dfs(bes); F0R(i,n) if (dist[i] > dist[bes]) bes = i;
    return dist[bes];
}