/**
* Description: 
* Source: GeeksForGeeks (corrected)
* Verification: USACO December 2017, Push a Box
    * https://pastebin.com/yUWuzTH8
*/

template<int SZ> struct BCC {
    int N;
    vi adj[SZ];
    vector<vpi> fin;
    
    void addEdge(int u, int v) { adj[u].pb(v), adj[v].pb(u); }
    
    int ti = 0, disc[SZ], low[SZ], comp[SZ], par[SZ];
    vpi st;

    void BCCutil(int u, bool root = 0) {
        disc[u] = low[u] = ti++;
        int child = 0;
        
        for (int i: adj[u]) if (i != par[u]) 
            if (disc[i] == -1) {
                child ++; par[i] = u;
                st.pb({u,i});
                BCCutil(i);
                low[u] = min(low[u],low[i]);
                
                if ((root && child > 1) || (!root && disc[u] <= low[i])) { // articulation point!
                    vpi tmp;
                    while (st.back() != mp(u,i)) tmp.pb(st.back()), st.pop_back();
                    tmp.pb(st.back()), st.pop_back();
                    fin.pb(tmp);
                }
            } else if (disc[i] < disc[u]) {
                low[u] = min(low[u],disc[i]);
                st.pb({u,i});
            }
    }
    
    void bcc(int _N) {
        N = _N;
        FOR(i,1,N+1) par[i] = disc[i] = low[i] = -1;
        FOR(i,1,N+1) if (disc[i] == -1) {
            BCCutil(i,1);
            if (sz(st)) fin.pb(st);
            st.clear();
        }
    }
};
