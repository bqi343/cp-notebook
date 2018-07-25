/**
* Description: shortest path!
* Works with negative edge weights (aka SPFA?)
*/

template<int SZ> struct Dijkstra {
    ll dist[SZ];
    vpi adj[SZ];
    priority_queue<pl,vpl,greater<pl>> q;
    
    void addEdge(int A, int B, int C) {
        adj[A].pb({B,C}), adj[B].pb({A,C});
    }
    
    void gen(int st) {
        fill_n(dist,SZ,INF); 
        q = priority_queue<pl,vpl,greater<pl>>();
        
        dist[st] = 0; q.push({0,st});
    	while (sz(q)) {
    		pl x = q.top(); q.pop();
    		if (dist[x.s] < x.f) continue;
    		for (pi y: adj[x.s]) if (x.f+y.s < dist[y.f]) {
    			dist[y.f] = x.f+y.s;
    			q.push({dist[y.f],y.f});
    		}
    	}
    }
};
