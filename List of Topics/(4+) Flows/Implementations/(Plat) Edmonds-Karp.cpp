// http://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/

const int SZ = 100;
  
struct Edge {
    int v, flow, C, rev;
};
 
pii pre[SZ];
int flow[SZ], SC, SNC;
vector<Edge> adj[SZ]; 
 
void addEdge(int u, int v, int C) {
    Edge a{v, 0, C, (int)adj[v].size()};
    Edge b{u, 0, 0, (int)adj[u].size()};
    adj[u].pb(a);
    adj[v].pb(b); 
} 

bool bfs() {
    memset(flow,0,sizeof flow);
    flow[SC] = MOD;
    
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

int maxflow(int sc, int snc) {
    SC = sc, SNC = snc;
    
    int ans = 0;
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

int main() {
    addEdge(0, 1, 16 );
    addEdge(0, 2, 13 );
    addEdge(1, 2, 10 );
    addEdge(1, 3, 12 );
    addEdge(2, 1, 4 );
    addEdge(2, 4, 14);
    addEdge(3, 2, 9 );
    addEdge(3, 5, 20 );
    addEdge(4, 3, 7 );
    addEdge(4, 5, 4);
    
    cout << "Maximum flow " << maxflow(0, 5);
}