/**
* Description: Euler Tour LCA w/ O(1) query
* Source: own
* Verification: Debug the Bugs
* Dependency: Range Minimum Query
*/

const int MAXN = 100001;

struct LCA {
    vi edges[MAXN];
    RMQ<pii,2*MAXN> r;
    vector<pii> tmp;
    int depth[MAXN], pos[MAXN];
    
    int V, R;
    
    void addEdge(int u, int v) {
        edges[u].pb(v), edges[v].pb(u);
    }
    
    void dfs(int u, int prev){
        pos[u] = sz(tmp); depth[u] = depth[prev]+1;
        tmp.pb({depth[u],u});
        for (int v: edges[u]) if (v != prev) {
            dfs(v, u);
            tmp.pb({depth[u],u});
        }
    }
    
    void construct() {
        dfs(R, 0);
        r.build(tmp);
    }
    
    int lca(int u, int v){
        u = pos[u], v = pos[v];
        if (u > v) swap(u,v);
        return r.query(u,v).s;
    }
    
    int dist(int u, int v) {
        return depth[u]+depth[v]-2*depth[lca(u,v)];
    }
};