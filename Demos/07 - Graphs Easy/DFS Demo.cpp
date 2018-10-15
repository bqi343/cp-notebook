
int main() {
	cin >> n;
	F0R(i,n-1) {
	    int a,b; cin >> a >> b;
	    adj[a].pb(b), adj[b].pb(a);
	}
	dfs(1);
}