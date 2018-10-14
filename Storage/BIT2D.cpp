

int main() {
	int T; cin >> T;
	F0R(i,T) {
	    int N; cin >> N;
	    BIT2D<ll,1024> B = BIT2D<ll,1024>();
	    while (1) {
	        string c; cin >> c;
	        if (c == "SET") {
	            int x, y,num; cin >> x >> y >> num;
	            x++, y++;
	            B.upd(x,y,num-B.query(x,x,y,y));
	        } else if (c == "SUM") {
	            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
	            x1 ++, y1 ++, x2 ++, y2++;
	            cout << B.query(x1,x2,y1,y2) << "\n";
	        } else break;
	    }
	}
}