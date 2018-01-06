/**
* Debug the Bugs
* Description: Use for both LCA's
*/

RMQ2 L;

int Q;

int main() {
    cin >> L.V >> Q >> L.R;
    F0R(i,L.V-1) {
        int u,v; cin >> u >> v;
        L.addEdge(u,v);
    }
    L.construct();
    
    F0R(i,Q) {
        int u,v; cin >> u >> v;
        cout << L.lca(u,v) << "\n";
    }
}
