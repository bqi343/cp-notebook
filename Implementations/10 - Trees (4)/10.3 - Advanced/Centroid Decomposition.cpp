/**
* Source: own
* Verification: https://codeforces.com/contest/342/problem/E
* Description: can support tree path queries and updates
*/

template<int SZ> struct CentroidDecomp {
    bool done[SZ];
    int sub[SZ], par[SZ], ans[SZ];
    vi dist[SZ], adj[SZ], ANS[SZ];
    pi cen[SZ];
    
    void addEdge(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
    
    void dfs (int no) {
        sub[no] = 1;
        for (int i: adj[no]) if (!done[i] && i != par[no]) {
            par[i] = no;
            dfs(i);
            sub[no] += sub[i];
        }
    }
    
    void genDist(int par, int no) {
        for (int i: adj[no]) if (!done[i] && i != par) {
            cen[i] = cen[no]; 
            dist[i].pb(dist[no].back()+1);
            genDist(no,i);
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
    
    void solve (int x) { // call solve(1) to initialize
        x = getCentroid(x); done[x] = 1;
        dist[x].pb(0);
        for (int i: adj[x]) if (!done[i]) {
            cen[i] = {x,sz(ANS[x])}; 
            dist[i].pb(1);
            genDist(x,i);
            ANS[x].pb(0);
        }
        for (int i: adj[x]) if (!done[i]) solve(i);
    }
    
    void upd(int v) {
        pi V = {v,-1};
        for (int ind = sz(dist[v])-1; V.f; V = cen[V.f], ind --) {
            ans[V.f] ++;
            if (V.s != -1) ANS[V.f][V.s] ++;
        }
    }
    
    int query(int v) {
        pi V = {v,-1}; int ret = 0;
        for (int ind = sz(dist[v])-1; V.f; V = cen[V.f], ind --) {
            ret += ans[V.f];
            if (V.s != -1) ret -= ANS[V.f][V.s];
        }
        return ret;
    }
};
