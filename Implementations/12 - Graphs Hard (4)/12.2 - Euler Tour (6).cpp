/**
* Description: extra log factor
* Verification: https://open.kattis.com/problems/eulerianpath
*/

struct Euler {
    vi circuit;
    multiset<int> adj[MX], ADJ[MX];
    int N,M, out[MX], in[MX];
    
    void find_circuit(int x) { // directed graph, possible that resulting circuit is not valid
        while (sz(adj[x])) {
            int j = *adj[x].begin(); adj[x].erase(adj[x].begin());
            find_circuit(j);
        }
        circuit.pb(x);
    }
    
    int a,b,start; 
    
    vi solve() {
        F0R(i,N) {
            adj[i].clear(), ADJ[i].clear();
            out[i] = in[i] = 0;
        }
        circuit.clear();
        F0R(i,M) {
            cin >> a >> b; // add edges
            adj[a].insert(b), ADJ[a].insert(b);
            out[a] ++, in[b] ++;
        }
        start = a;
        F0R(i,N) if (out[i]-in[i] == 1) start = i;
        
        find_circuit(start);
        reverse(all(circuit));
        
        if (sz(circuit) != M+1) return {};
        
        F0R(i,M) { // verify that circuit is valid
            if (ADJ[circuit[i]].find(circuit[i+1]) == ADJ[circuit[i]].end()) return {};
            int t = circuit[i];
            ADJ[t].erase(ADJ[t].find(circuit[i+1]));
        }
        
        return circuit;
    }
};
