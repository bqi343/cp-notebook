int n, visit[MX];
vi adj[MX];

void dfs(int node) {
    if (visit[node]) return;
    visit[node] = 1;
    for (int i: adj[node]) dfs(i);
    cout << node << "\n";
	// do stuff

}

int main() {
	cin >> n;
	F0R(i,n-1) {
	    int a,b; cin >> a >> b;
	    adj[a].pb(b), adj[b].pb(a);
	}
	dfs(1);
}