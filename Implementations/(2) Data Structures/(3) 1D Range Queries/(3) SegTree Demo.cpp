// SPOJ fenwick

BIT<ll,1000000> B;
// Seg<ll,1<<20> B;

int main() {
	int N; cin >> N;
	FOR(i,1,N+1) {
	    int x; cin >> x;
	    B.upd(i,x);
	}
	int q; cin >> q;
	F0R(i,q) {
	    char c; int a, b; 
	    cin >> c >> a >> b;
	    if (c == 'q') cout << B.query(a,b) << "\n";
	    else B.upd(a,b);
	}
}