/**
* Link: http://www.spoj.com/problems/HORRIBLE/
* Description: Use with range BIT, lazy segtree
*/

int main() {
    int T; cin >> T;
    F0R(i,T) {
        LazySegTree<ll,1<<17> B = LazySegTree<ll,1<<17>(); 
        int N, C; cin >> N >> C;
        F0R(j,C) {
            int t; cin >> t;
            if (t == 0) {
                int p,q,v; cin >> p >> q >> v;
                B.upd(p,q,v);
            } else {
                int p,q; cin >> p >> q;
                cout << B.qsum(p,q) << "\n"; 
            }
        }
    }
}