/**
* Source: own
* Verification: https://codeforces.com/contest/342/problem/E
* Description: supports the following operations on a tree
 * making node red
 * querying distance to closest red node
*/

template<int SZ> struct centroidDecomp {
    int N;
    bool done[SZ];
    int sub[SZ], par[SZ], ans[SZ], cen[SZ];
    vi dist[SZ], adj[SZ];
    
    // INITIALIZE
    
    void addEdge(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
    
    void dfs (int no) {
        sub[no] = 1;
        for (int i: adj[no]) if (!done[i] && i != par[no]) {
            par[i] = no;
            dfs(i);
            sub[no] += sub[i];
        }
    }
    
    void genDist(int par, int no, int t, int dis) {
        dist[no].pb(dis);
        for (int i: adj[no]) if (!done[i] && i != par) {
            cen[i] = t;
            genDist(no,i,t,dis+1);
        }
    }
    
    int getCentroid(int x) {
        par[x] = 0; dfs(x);
        int sz = sub[x];
        while (1) {
            pi mx = {0,0};
            for (int i: adj[x]) if (!done[i] && i != par[x]) mx = max(mx,{sub[i],i});
            if (mx.f*2 > sz) x = mx.s;
            else return x;
        }
    }
    
    void solve (int x) {
        x = getCentroid(x); done[x] = 1;
        genDist(0,x,x,0);
        for (int i: adj[x]) if (!done[i]) solve(i);
    }
    
    void init() {
    	FOR(i,1,N+1) ans[i] = MOD;
    	solve(1);
    }
    
    // QUERY 
    
    void upd(int v) {
        for (int V = v, ind = sz(dist[v])-1; V; V = cen[V], ind --) 
            ans[V] = min(ans[V],dist[v][ind]);
    }
    
    int query(int v) {
        int ret = MOD;
        for (int V = v, ind = sz(dist[v])-1; V; V = cen[V], ind --) 
            ret = min(ret,ans[V]+dist[v][ind]);
        return ret;
    }
};
