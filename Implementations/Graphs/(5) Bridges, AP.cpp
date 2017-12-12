// http://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/

vi adj[100001];
vector<pii> bridge;
int n,m, disc[100001], low[100001], art[100001], nex = 1;

void dfs(int pre, int node) {
    low[node] = disc[node] = nex++;
    
    int child = 0;
    for (int i: adj[node]) if (i != pre) {
        if (!disc[i]) {
            child++; dfs(node,i);
            if (disc[node] < low[i]) bridge.pb({node,i}); // check for bridge
            
            if (pre == 0) { // check for articulation point
                if (child > 1) art[node] = 1;
            } else if (disc[node] <= low[i]) art[node] = 1;
            
            low[node] = min(low[node],low[i]);
        } else low[node] = min(low[node],disc[i]);
    }
}

int main() {
    cin >> n >> m;
    F0R(i,m) {
        int x,y; cin >> x >> y;
        adj[x].pb(y), adj[y].pb(x);
    }
    dfs(0,1);
    cout << "Bridges\n";
    for (pii x: bridge) cout << x.f << " " << x.s << "\n";
    cout << "\n";
    
    cout << "Articulation Points\n";
    FOR(i,1,n+1) if (art[i]) cout << i << "\n";
}