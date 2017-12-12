// https://open.kattis.com/problems/eulerianpath
// extra log factor

vi circuit;
multiset<int> adj[10000], adj1[10000];
int N,M, out[10000], in[10000];

void find_circuit(int x) { // directed graph, possible that resulting circuit is not valid
    while (adj[x].size()) {
        int j = *adj[x].begin(); adj[x].erase(adj[x].begin());
        find_circuit(j);
    }
    circuit.pb(x);
}

int a,b,start; 

void solve() {
    F0R(i,N) {
        adj[i].clear(), adj1[i].clear();
        out[i] = in[i] = 0;
    }
    circuit.clear();
    F0R(i,M) {
        cin >> a >> b; 
        adj[a].insert(b), adj1[a].insert(b);
        out[a] ++, in[b] ++;
    }
    start = a;
    F0R(i,N) if (out[i]-in[i] == 1) start = i;
    
    find_circuit(start);
    reverse(circuit.begin(),circuit.end());
    
    if (circuit.size() != M+1) {
        cout << "Impossible\n";
        return;
    }
    
    F0R(i,M) {
        if (adj1[circuit[i]].find(circuit[i+1]) == adj1[circuit[i]].end()) {
            cout << "Impossible\n";
            return;
        }
        adj1[circuit[i]].erase(adj1[circuit[i]].find(circuit[i+1]));
    }
    F0R(i,M+1) cout << circuit[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    while (cin >> N >> M) {
        if (N+M == 0) break;
        solve();
    }
}
