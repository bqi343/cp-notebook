/**
* Description: Euler Tour LCA w/ O(1) query
* Source: own
*/

const int MAXN = 100001, MAXK = 17;

int Q;

struct RMQ2 {
    vi edges[MAXN];
    pii rmq[MAXK][2*MAXN];
    int depth[MAXN], pos[MAXN];
    
    int N, nex=0;
    
    void addEdge(int u, int v) {
        edges[u].pb(v), edges[v].pb(u);
    }
    
    void dfs(int u, int prev){
        pos[u] = nex; depth[u] = depth[prev]+1;
        rmq[0][nex++] = {depth[u],u};
        for (int v: edges[u]) if (v != prev) {
            dfs(v, u);
            rmq[0][nex++] = {depth[u],u};
        }
    }
    
    void construct() {
        dfs(1, 0);
        FOR(k,1,MAXK) F0R(i,nex) if (i+(1<<(k-1)) < nex) rmq[k][i] = min(rmq[k-1][i],rmq[k-1][i+(1<<(k-1))]);
    }
    
    int lca(int u, int v){
        u = pos[u], v = pos[v];
        if (u > v) swap(u,v);
        int x = 31-__builtin_clz(v-u+1);
        return min(rmq[x][u],rmq[x][v-(1<<x)+1]).s;
    }
    
    int dist(int u, int v) {
        return depth[u]+depth[v]-2*depth[lca(u,v)];
    }
};

RMQ2 R;

int main(){
    cin >> R.N >> Q;
    F0R(i,R.N-1) {
        int u,v; cin >> u >> v;
        R.addEdge(u,v);
    }
    R.construct();
    
    F0R(i,Q) {
        int u,v; cin >> u >> v;
        cout << R.dist(u,v) << "\n";
    }
}
