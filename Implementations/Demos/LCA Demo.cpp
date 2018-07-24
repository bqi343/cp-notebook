/**
* Debug the Bugs
* Description: Use for both LCA's
*/

LCA<MX> L;

int N,Q;

int main() {
    cin >> N >> Q >> L.R;
    F0R(i,N-1) {
        int u,v; cin >> u >> v;
        L.addEdge(u,v);
    }
    L.init(N);
    
    F0R(i,Q) {
        int u,v; cin >> u >> v;
        cout << L.lca(u,v) << "\n";
    }
}