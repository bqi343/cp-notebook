/**
 * Description: computes biconnected components
 * Source: GeeksForGeeks (corrected)
 * Verification: USACO December 2017, Push a Box
    * https://pastebin.com/yUWuzTH8
 */

template<int SZ> struct BCC {
    int N;
    vpi adj[SZ], ed;

    void addEdge(int u, int v) { 
        adj[u].pb({v,sz(ed)}), 
        adj[v].pb({u,sz(ed)}); 
        ed.pb({u,v});
    }

    int ti = 0, disc[SZ];
    vi st; vector<vi> fin;

    int bcc(int u, int p = -1) { // return lowest disc
        disc[u] = ++ti; int low = disc[u];
        int child = 0;
        trav(i,adj[u]) if (i.s != p)
            if (!disc[i.f]) {
                child ++; st.pb(i.s);
                int LOW = bcc(i.f,i.s); ckmin(low,LOW);
                // disc[u] < LOW -> bridge
                if (disc[u] <= LOW) { 
                    // if (p != -1 || child > 1) -> u is articulation point
                    vi tmp; while (st.back() != i.s) tmp.pb(st.back()), st.pop_back();
                    tmp.pb(st.back()), st.pop_back();
                    fin.pb(tmp); 
                }
            } else if (disc[i.f] < disc[u]) {
                ckmin(low,disc[i.f]);
                st.pb(i.s);
            }
        return low;
    }

    void init(int _N) {
        N = _N; FOR(i,1,N+1) disc[i] = 0;
        FOR(i,1,N+1) if (!disc[i]) bcc(i); // st should be empty after each iteration
    }
};
