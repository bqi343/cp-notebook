

Seg S = Seg();
    
void solve() {
	cin >> N >> M;
	F0R(i,N) cin >> a[i];
	S.build();
	
	F0R(i,M) {
	    int t; cin >> t;
	    if (t == 0) {
	        int x,y,z; cin >> x >> y >> z;
	        S.modify(x-1,y-1,z);
	    } else if (t == 1) {
	        int x,y; cin >> x >> y;
	        cout << S.qmax(x-1,y-1) << "\n";
	    } else {
	        int x,y; cin >> x >> y;
	        cout << S.qsum(x-1,y-1) << "\n";
	    }
	}
}