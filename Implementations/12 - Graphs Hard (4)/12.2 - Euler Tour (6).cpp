/**
* Description: O(N+M) euler tour for both directed and undirected graphs
* Source: USACO Training
* Verification: 
    * directed: https://open.kattis.com/problems/eulerianpath
    * undirected: USACO Training 3.3, Riding the Fences
*/

struct Euler {
    vpi adj[MX], circuit;
    int N, M, nex, out[MX], in[MX], deg[MX];
    bool used[MX], bad;
    
    void clr() {
        F0R(i,N) adj[i].clear();
        circuit.clear(); 
        nex = 0;
        F0R(i,N) out[i] = in[i] = deg[i];
        F0R(i,M) used[i] = 0;
        bad = 0;
    }
    
    void find_circuit(int pre, int cur) { 
        while (sz(adj[cur])) {
            pi x = adj[cur].back(); adj[cur].pop_back();
            if (used[x.s]) continue;
            used[x.s] = 1; 
            find_circuit(cur,x.f);
        }
        if (sz(circuit) && circuit.back().f != cur) bad = 1;
        circuit.pb({pre,cur});
    }
    
    void addEdge(int a, int b, bool directed) {
        if (directed) {
            adj[a].pb({b,nex}); 
            out[a] ++, in[b] ++; nex ++;
        } else {
            adj[a].pb({b,nex}), adj[b].pb({a,nex});
            deg[a] ++, deg[b] ++; nex ++;
        }
    }
    
    vi solve(bool directed) { // edges only involve vertices from 0 to N-1
        int start = 0;
        F0R(i,N) if (deg[i] || in[i] || out[i]) start = i;
        
        if (directed) {
            F0R(i,N) if (out[i]-in[i] == 1) start = i;
        } else {
            F0R(i,N) if (deg[i] % 2 == 1) start = i;
        }
        
        find_circuit(-1,start);
        if (sz(circuit) != M+1 || bad) return {};
        vi ans; F0Rd(i,sz(circuit)) ans.pb(circuit[i].s);
        return ans;
    }
};
