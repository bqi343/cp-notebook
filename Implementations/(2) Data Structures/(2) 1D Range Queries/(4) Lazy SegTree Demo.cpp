// SPOJ horrible

int main() {
    int T; cin >> T;
    F0R(i,T) {
        BITrange<ll,100000> B = BITrange<ll,100000>(); // LazySegTree<ll,1<<17>
        int N, C; cin >> N >> C;
        F0R(j,C) {
            int t; cin >> t;
            if (t == 0) {
                int p,q,v; cin >> p >> q >> v;
                B.upd(p,q,v);
            } else {
                int p,q; cin >> p >> q;
                cout << B.query(p,q) << "\n"; // qsum
            }
        }
    }
}