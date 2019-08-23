/**
 * Source: own
 * Verification: 
    * Triway Cup 2019 G
    * https://codeforces.com/contest/342/problem/E
 * Description: can support tree path queries and updates
 */

template<int SZ> struct CD {
    struct Edge { 
        int a,b,w; 
        int other(int x) { return a+b-x; }
    };
    vector<Edge> ed;
    vi adj[SZ];
    
    bool done[SZ];
    int sub[SZ], par[SZ];
    vl dist[SZ];
    pi cen[SZ];

    void addEdge(int a, int b, int w = 1) { 
        adj[a].pb(sz(ed)), adj[b].pb(sz(ed));
        ed.pb({a,b,w});
    }

    void dfs (int x) {
        sub[x] = 1;
        trav(i,adj[x]) {
            int y = ed[i].other(x);
            if (!done[y] && y != par[x]) {
                par[y] = x; dfs(y);
                sub[x] += sub[y];
            }
        }
    }

    void genDist(int p, int x) {
        trav(i,adj[x]) {
            int y = ed[i].other(x);
            if (!done[y] && y != p) {
                cen[y] = cen[x]; dist[y].pb(dist[x].back()+ed[i].w);
                genDist(x,y);
            }
        }
    }

    int centroid(int x) {
        par[x] = -1;  dfs(x); 
        for (int sz = sub[x];;) {
            pi mx = {0,0};
            trav(i,adj[x]) {
                int y = ed[i].other(x);
                if (!done[y] && y != par[x]) ckmax(mx,{sub[y],y});
            }
            if (mx.f*2 <= sz) return x; 
            x = mx.s;
        }
    }

    void gen(int x, bool fst = 0) { // call init(1) to start
        done[x = centroid(x)] = 1; dist[x].pb(0); // exit(0);
        if (fst) cen[x].f = -1;
        int co = 0;
        trav(i,adj[x]) {
            int y = ed[i].other(x);
            if (!done[y]) {
                cen[y] = {x,co++}; dist[y].pb(ed[i].w);
                genDist(x,y);
            }
        }
        trav(i,adj[x]) {
            int y = ed[i].other(x);
            if (!done[y]) gen(y);
        }
    }
    
    void init() { gen(0,1); }
};