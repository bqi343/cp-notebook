/*
 * Description: O(EV) Bipartite Matching
 * Source: own
 * Verification: USACO Training unmatch
 */

struct MaxMatch {
    int N, flow = 0;
    int match[MX], rmatch[MX];
    bitset<MX> vis;
    vi adj[MX];

    MaxMatch() { F0R(i,MX) match[i] = rmatch[i] = 0; }
    
    void connect(int a, int b, bool c = 1) {
        if (c) match[a] = b, rmatch[b] = a;
        else match[a] = rmatch[b] = 0;
    }
    bool dfs(int x) {
        if (!x) return 1;
        if (vis[x]) return 0;
        vis[x] = 1;
        trav(t,adj[x]) if (t != match[x] && dfs(rmatch[t])) {
            connect(x,t); return 1;
        }
        return 0;
    }
    void tri(int x) { vis.reset(); flow += dfs(x); }

    void init(int _N) { 
        N = _N;
        FOR(i,1,N+1) if (!match[i]) tri(i); 
    }
};