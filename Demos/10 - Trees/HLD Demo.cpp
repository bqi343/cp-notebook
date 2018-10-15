HeavyLight<1<<17> H;
int N,M;

int main() {
	cin >> N >> M;
	graph.resize(N+1);
	F0R(i,N-1) {
	    int a,b; cin >> a >> b;
	    graph[a].pb(b), graph[b].pb(a);
	}
	H.init();
	F0R(i,M) {
	    char c; int A,B;
	    cin >> c >> A >> B;
	    if (c == 'P') H.modifyPath(A,B,1);
	    else cout << H.queryPath(A,B) << "\n";
	}
}
