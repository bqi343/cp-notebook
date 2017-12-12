int N,M, in[100001];
vi res, adj[100001];

void topo() {
    queue<int> todo;
    FOR(i,1,N+1) if (in[i] == 0) todo.push(i);
    while (todo.size()) {
        int x = todo.front(); todo.pop();
        res.pb(x);
        for (int i: adj[x]) {
            in[i] --;
            if (in[i] == 0) todo.push(i);
        }
    }
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> M;
	F0R(i,M) {
	    int x,y; cin >> x >> y;
	    adj[x].pb(y), in[y] ++;
	}
	topo();
	for (int i: res) cout << i << " ";
}

// read!
// ll vs. int!