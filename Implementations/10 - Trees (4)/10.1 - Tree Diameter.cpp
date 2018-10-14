/**
* Description: Calculates longest path in tree
* Source: Own
* Verification: http://www.spoj.com/problems/PT07Z/
*/

struct TreeDiameter {
    int n, dist[MX], pre[MX];
    vi adj[MX];

    void addEdge(int a, int b) {
        adj[a].pb(b), adj[b].pb(a);
    }

    void dfs(int cur) {
        for (int i: adj[cur]) if (i != pre[cur]) {
            pre[i] = cur;
            dist[i] = dist[cur]+1;
            dfs(i);
        }
    }

    void genDist(int cur) {
        memset(dist,0,sizeof dist);
        pre[cur] = -1;
        dfs(cur);
    }

    int diameterLength() {
        genDist(1);
        int bes = 0; FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i;
        genDist(bes); FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i;
        return dist[bes];
    }

    vi genCenter() {
        int t = diameterLength();
        int bes = 0; FOR(i,1,n+1) if (dist[i] > dist[bes]) bes = i;
        
        F0R(i,t/2) bes = pre[bes];
        if (t&1) return {bes,pre[bes]};
        return {bes};
    }
};