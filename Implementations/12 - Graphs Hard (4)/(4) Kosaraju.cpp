/**
* Source: Wikipedia
* Description: generates SCC in topological order, support for 2-SAT
* Verification: POI 8 peaceful commission
*/ 

int rev(int x) {
    return x&1?x+1:x-1;
}

template<int SZ> struct scc {
    vi adj[SZ], radj[SZ], todo, allComp;
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
    	for (int i: todo) if (!comp[i]) {
    	    dfs2(i,i);
    	    allComp.pb(i);
    	}
    }
    
    int tmp[SZ];
    bitset<SZ> ans;
    
    bool twosat() {
    	for (int i = 1; i <= N; i += 2) if (comp[i] == comp[rev(i)]) return 0;
    	reverse(all(allComp));
    	for (int i: allComp) if (tmp[i] == 0) {
    	    tmp[i] = 1;
    	    tmp[comp[rev(i)]] = -1;
    	}
	    FOR(i,1,N+1) if (tmp[comp[i]] == 1) ans[i] = 1;
    	return 1;
    }
};