int main() {
    setIO(); 
    Euler E;
    while (cin >> E.N >> E.M) {
        if (E.N == 0) break;
        E.clr();
        F0R(i,E.M) {
            int a,b; re(a,b);
            E.addEdge(a,b,1);
        }
        auto res = E.solve(1);
        if (sz(res) == 0) cout << "Impossible";
        else {
            for (int i: res) cout << i << " ";
        }
        cout << "\n";
    }
}