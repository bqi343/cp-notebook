

Aho<MX> A;

int n;

void solve() {
    A = Aho<MX>();
    cin >> n;
    F0R(i,n) {
        string pat; getline(cin,pat); if (!i) getline(cin,pat);
        A.add(pat);
    }
    A.push_links();
    
    string t; getline(cin,t);
    int cur = 0;
    F0R(i,sz(t)) cur = A.nex(i,cur,t[i]);
    FOR(i,1,n+1) {
        for (int j: A.oc[i]) cout << j << " ";
        cout << "\n";
    }
}
