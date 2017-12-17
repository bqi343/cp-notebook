const int MX = 100001;

struct scc {
    vi adj[MX], radj[MX], todo;
    int comp[MX], N, M;
    bool visit[MX];

    scc() {
        memset(comp,0,sizeof comp);
        memset(visit,0,sizeof visit);
    }
    
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
		adj[a].pb(b);
		radj[b].pb(a);
    }
    
    void genSCC() {
    	FOR(i,1,N+1) if (!visit[i]) dfs(i);
    	reverse(todo.begin(),todo.end());
    	for (int i: todo) if (!comp[i]) dfs2(i,i);
    }
};

scc S;

int main() {
	cin >> S.N >> S.M;
	F0R(i,S.M) {
		int a,b; cin >> a >> b;
		S.addEdge(a,b);
	}
	S.genSCC();
}
