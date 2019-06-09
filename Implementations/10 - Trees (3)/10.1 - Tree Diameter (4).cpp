/**
 * Description: Calculates longest path in tree
 * Source: own
 * Verification: http://www.spoj.com/problems/PT07Z/
 */

template<int SZ> struct TreeDiameter {
    struct Edge { 
        int a,b,w; 
        int other(int x) { return a+b-x; }
    };
    vector<Edge> ed;
    vi adj[SZ];
    void addEdge(int a, int b) { // can adjust to allow diameter w/ weights
        adj[a].pb(sz(ed)), adj[b].pb(sz(ed));
        ed.pb({a,b,1});
    }

    int par[SZ];
    ll dist[SZ];
    void dfs(int x) {
        trav(i,adj[x]) {
            int y = ed[i].other(x);
            if (y != par[x]) {
                par[y] = x; dist[y] = dist[x]+ed[i].w;
                dfs(y);
            }
        }
    }
    void genDist(int x) {
        par[x] = -1; dist[x] = 0; dfs(x);
    }

    int n; vi center; int dia;
    void init(int _n) {
        n = _n; genDist(1);
        int bes = 0; FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i; // bes is now one endpoint of a diameter
        genDist(bes); FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i;
        dia = dist[bes];
        F0R(i,dia/2) bes = par[bes];
        if (dia&1) center = {bes,par[bes]};
        else center = {bes};
    }
};