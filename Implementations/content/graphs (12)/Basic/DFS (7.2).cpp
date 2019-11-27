/**
 * Description: print nodes of graph in depth-first order
 * Source: Own
 */

bool visit[MX];
vi adj[MX];

void dfs(int node) {
    if (visit[node]) return;
    visit[node] = 1;
    trav(i,adj[node]) dfs(i);
    ps(node);
	// do stuff
}