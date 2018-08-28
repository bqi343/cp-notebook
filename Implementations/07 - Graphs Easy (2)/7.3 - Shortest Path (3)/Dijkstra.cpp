/**
* Description: shortest path!
* Works with negative edge weights (aka SPFA?)
*/

template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;

template<class T> T poll(pqg<T>& x) {
    T y = x.top(); x.pop();
    return y;
}

template<int SZ> struct Dijkstra {
    ll dist[SZ];
    vpi adj[SZ];
    pqg<pl> q;
    
    void addEdge(int A, int B, int C) {
        adj[A].pb({B,C}), adj[B].pb({A,C});
    }
    
    void gen(int st) {
        fill_n(dist,SZ,INF); 
        q = pqg<pl>(); q.push({dist[st] = 0,st});
    	while (sz(q)) {
    		auto x = poll(q);
    		if (dist[x.s] < x.f) continue;
    		for (auto y: adj[x.s]) if (x.f+y.s < dist[y.f]) 
    			q.push({dist[y.f] = x.f+y.s,y.f});
    	}
    }
};
