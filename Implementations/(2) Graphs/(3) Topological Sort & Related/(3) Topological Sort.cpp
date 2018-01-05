/**
* Description: sorts vertices such that if there exists an edge x->y, then x goes before y
*/

int N,M, in[100001];
vi res, adj[100001];

void topo() {
    queue<int> todo;
    FOR(i,1,N+1) if (in[i] == 0) todo.push(i);
    while (sz(todo)) {
        int x = todo.front(); todo.pop();
        res.pb(x);
        for (int i: adj[x]) {
            in[i] --;
            if (!in[i]) todo.push(i);
        }
    }
}

int main() {
	cin >> N >> M;
	F0R(i,M) {
	    int x,y; cin >> x >> y;
	    adj[x].pb(y), in[y] ++;
	}
	topo();
	for (int i: res) cout << i << " ";
}