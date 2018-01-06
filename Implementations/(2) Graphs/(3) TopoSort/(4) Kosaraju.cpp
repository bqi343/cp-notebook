/**
* Source: Wikipedia
* Description: generates SCC in topological order
* Verification: SPOJ capcity
*/ 

template<int SZ> struct scc {
    vi adj[SZ], radj[SZ], todo;
    int N, comp[SZ];
    bitset<SZ> visit;
    
    void dfs(int v) {
    	visit[v] = 1; 
    	for (int w: adj[v]) if (!visit[w]) dfs(w);
    	todo.pb(v);
    }
    
    void dfs2(int v, int val) {
    	comp[v] = val;
    	for (int w: radj[v]) if (!comp[w]) dfs2(w,val);
    }
    
    void addEdge(int a, int b) {
		adj[a].pb(b), radj[b].pb(a);
    }
    
    void genSCC() {
        FOR(i,1,N+1) comp[i] = visit[i] = 0;
    	FOR(i,1,N+1) if (!visit[i]) dfs(i);
    	reverse(all(todo)); // toposort 
    	for (int i: todo) if (!comp[i]) dfs2(i,i);
    }
};