/**
* Source: See BCC template
* Description: generates SCC in reverse topological order
*/ 

template<int SZ> struct scc {
    int N, ti = 0;
    vi adj[SZ], st, fin;
    int disc[SZ], low[SZ], comp[SZ];
    bitset<SZ> inStack;
    
    void addEdge(int u, int v) {
        adj[u].pb(v);
    }
    
    void SCCutil(int u) {
        disc[u] = low[u] = ti++;
        st.pb(u); inStack[u] = 1;
        
        for (int i: adj[u]) {
            if (disc[i] == -1) {
                SCCutil(i);
                low[u] = min(low[u],low[i]);
            } else if (inStack[i]) {
                low[u] = min(low[u],disc[i]);
            }
        }
        
        if (disc[u] == low[u]) {
            while (st.back() != u) {
                comp[st.back()] = u;
                inStack[st.back()] = 0;
                st.pop_back();
            }
            comp[u] = u; inStack[u] = 0; st.pop_back();
            fin.pb(u);
        }
    }
    
    void genSCC() {
        FOR(i,1,N+1) disc[i] = low[i] = -1;
        FOR(i,1,N+1) if (disc[i] == -1) SCCutil(i);
    }
};