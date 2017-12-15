// source: GeeksForGeeks

const int SZ = 1000;
 
struct Edge {
    int v, flow, C, rev;
};
 
struct Dinic {
    int level[SZ], start[SZ];
    vector<Edge> adj[SZ]; 
     
    void addEdge(int u, int v, int C) {
        Edge a{v, 0, C, (int)adj[v].size()};
        Edge b{u, 0, 0, (int)adj[u].size()};
        adj[u].pb(a);
        adj[v].pb(b); 
    } 
     
    bool BFS(int s, int t) {
        F0R(i,SZ) level[i] = -1;
        level[s] = 0;  
      
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto e: adj[u]) 
                if (level[e.v] < 0  && e.flow < e.C) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
        }
     
        return level[t] >= 0;
    }
      
    int sendFlow(int u, int flow, int t) {
        if (u == t) return flow;
      
        for (  ; start[u] < adj[u].size(); start[u] ++) {
            Edge &e = adj[u][start[u]]; 
                                          
            if (level[e.v] == level[u]+1 && e.flow < e.C) {
                int curr_flow = min(flow, e.C - e.flow);
                int temp_flow = sendFlow(e.v, curr_flow, t);
    
                if (temp_flow > 0) {
                    e.flow += temp_flow;
                    adj[e.v][e.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
      
        return 0;
    }
     
    int DinicMaxflow(int s, int t) {
        if (s == t) return -1;
        int total = 0;  
      
        while (BFS(s, t)) {
            F0R(i,SZ) start[i] = 0;
            while (int flow = sendFlow(s, INT_MAX, t)) total += flow;
        }
     
        return total;
    } 
};
  
Dinic D;

int main() {
    D.addEdge(0, 1, 16 );
    D.addEdge(0, 2, 13 );
    D.addEdge(1, 2, 10 );
    D.addEdge(1, 3, 12 );
    D.addEdge(2, 1, 4 );
    D.addEdge(2, 4, 14);
    D.addEdge(3, 2, 9 );
    D.addEdge(3, 5, 20 );
    D.addEdge(4, 3, 7 );
    D.addEdge(4, 5, 4);
  
    cout << "Maximum flow " << D.DinicMaxflow(0, 5);
}
