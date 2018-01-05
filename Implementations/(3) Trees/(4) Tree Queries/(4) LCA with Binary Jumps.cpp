/**
* Source: USACO Camp
* Verification: Debug the Bugs
*/

const int MAXN = 100001, MAXK = 17;

int Q;

struct LCA {
    int V, R;
    vi edges[MAXN];
    int parK[MAXK][MAXN];
    int depth[MAXN];
    
    void addEdge(int u, int v) {
        edges[u].pb(v), edges[v].pb(u);
    }
    
    void dfs(int u, int prev){
        parK[0][u] = prev;
        depth[u] = depth[prev]+1;
        for (int v: edges[u]) if (v != prev) dfs(v, u);
    }
    
    void construct() {
        dfs(R, 0);
        FOR(k,1,MAXK) FOR(i,1,V+1)
            parK[k][i] = parK[k-1][parK[k-1][i]];
    }
    
    int lca(int u, int v){
        if (depth[u] < depth[v]) swap(u,v);
        
        F0Rd(k,MAXK)  if (depth[u] >= depth[v]+(1<<k))  u = parK[k][u];
        F0Rd(k,MAXK) if (parK[k][u] != parK[k][v]) u = parK[k][u], v = parK[k][v];
        
        if(u != v) u = parK[0][u], v = parK[0][v];
        return u;
    }
    
    int dist(int u, int v) {
        return depth[u]+depth[v]-2*depth[lca(u,v)];
    }
};
