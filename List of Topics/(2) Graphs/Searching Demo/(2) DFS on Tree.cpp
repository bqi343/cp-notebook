// example use: http://codeforces.com/contest/839/problem/C

int n; // number of nodes
vi adj[100001]; // for each vertex store adjacent vertices

void dfs(int par, int node) { // store parent of the node so we don't dfs backwards
	for (int i: adj[node]) if (i != par) dfs(node,i); // dfs through all the children of node
	// do what you want

}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	F0R(i,n-1) {
	    int a,b; cin >> a >> b; // read in the edges
	    adj[a].pb(b);
	    adj[b].pb(a);
	}
	dfs(0,1); // dfs starting at the root, which has no parent (so we pass 0)
}
