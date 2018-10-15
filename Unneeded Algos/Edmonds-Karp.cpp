/**
* Source: GeeksForGeeks
*/

struct Edge {
    int v;
    ll flow, C;
    int rev;
};

template<int SZ> struct EdmondsKarp {
    pi pre[SZ];
    int SC, SNC;
    ll flow[SZ];
    vector<Edge> adj[SZ]; 
     
    void addEdge(int u, int v, int C) {
        Edge a{v, 0, C, sz(adj[v])};
        Edge b{u, 0, 0, sz(adj[u])};
        adj[u].pb(a), adj[v].pb(b); 
    } 

    bool bfs() {
        memset(flow,0,sizeof flow);
        flow[SC] = INF;
        
        queue<int> todo; todo.push(SC);
        while (todo.size()) {
            if (flow[SNC]) break;
            int x = todo.front(); todo.pop();
            for (auto a: adj[x]) if (!flow[a.v] && a.flow < a.C) {
                pre[a.v] = {x,a.rev};
                flow[a.v] = min(flow[x],a.C-a.flow);
                todo.push(a.v);
            }
        }
        
        return flow[SNC];
    }

    ll maxFlow(int sc, int snc) {
        SC = sc, SNC = snc;
        
        ll ans = 0;
        while (bfs()) {
            ans += flow[SNC];
            for (int x = SNC; x != SC; x = pre[x].f) {
                adj[x][pre[x].s].flow -= flow[SNC];
                int t = adj[x][pre[x].s].rev;
                adj[pre[x].f][t].flow += flow[SNC];
            }
        }
        
        return ans;
    }
};