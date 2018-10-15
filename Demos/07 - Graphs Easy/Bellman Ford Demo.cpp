BellmanFord<1000> B;

int main() {
    setIO();
    int m,q,s;
    while (cin >> B.n >> m >> q >> s) {
        if (B.n == 0) break;
        B.edge.clear();
        F0R(i,m) {
            int u,v,w; re(u,v,w);
            B.edge.pb({{u,v},w});
        }
        B.gen(s);
        F0R(i,q) {
            int x; re(x);
            ll t = B.query(x);
            if (t == -INF) cout << "-Infinity";
            else if (t == INF) cout << "Impossible";
            else cout << t;
            cout << "\n";
        }
        cout << "\n";
    }
}