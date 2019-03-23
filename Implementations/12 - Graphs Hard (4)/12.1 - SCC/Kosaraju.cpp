/**
 * Source: Wikipedia
 * Description: generates SCC in topological order
 * Verification: POI 8 peaceful commission
 */

template<int SZ> struct scc {
    int N, comp[SZ];
    vi adj[SZ], radj[SZ], todo, allComp;
    bitset<SZ> visit;
    
    void addEdge(int a, int b) { adj[a].pb(b), radj[b].pb(a); }

    void dfs(int v) {
        visit[v] = 1;
        trav(w,adj[v]) if (!visit[w]) dfs(w);
        todo.pb(v);
    }

    void dfs2(int v, int val) {
        comp[v] = val;
        trav(w,radj[v]) if (comp[w] == -1) dfs2(w,val);
    }

    void genSCC() { // fills allComp
        F0R(i,N) comp[i] = -1, visit[i] = 0;
        F0R(i,N) if (!visit[i]) dfs(i);
        reverse(all(todo)); // toposort
        trav(i,todo) if (comp[i] == -1) dfs2(i,i), allComp.pb(i);
    }
};
