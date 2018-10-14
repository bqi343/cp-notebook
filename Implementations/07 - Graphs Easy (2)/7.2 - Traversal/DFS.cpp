/**
* Description: print nodes of graph in depth-first order
* Source: Own
*/

bool visit[MX];
vi adj[MX];

void dfs(int node) {
    if (visit[node]) return;
    visit[node] = 1;
    for (int i: adj[node]) dfs(i);
    cout << node << "\n";
	// do stuff
}