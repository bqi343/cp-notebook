/**
* Description: shortest path!
* Works with negative edge weights (aka SPFA?)
*/

template<int SZ> struct Dijkstra {
    int dist[SZ];
    vpi adj[SZ];
    priority_queue<pi,vpi,greater<pi>> q;
    
    void gen() {
        fill_n(dist,SZ,MOD); dist[0] = 0; 
	
    	q.push({0,0});
    	while (sz(q)) {
    		pi x = q.top(); q.pop();
    		if (dist[x.s] < x.f) continue;
    		for (pi y: adj[x.s]) if (x.f+y.s < dist[y.f]) {
    			dist[y.f] = x.f+y.s;
    			q.push({dist[y.f],y.f});
    		}
    	}
    }
};
