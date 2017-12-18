/**
* Source: own
*/

template<int SZ> struct Dijkstra {
    int dist[SZ];
    vector<pii> adj[SZ];
    priority_queue<pii,vector<pii>,greater<pii>> q;
    
    void gen() {
        fill_n(dist,SZ,MOD); dist[0] = 0; 
	
    	q.push({0,0});
    	while (q.size()) {
    		pii x = q.top(); q.pop();
    		if (dist[x.s] < x.f) continue;
    		for (pii y: adj[x.s]) if (x.f+y.s < dist[y.f]) {
    			dist[y.f] = x.f+y.s;
    			q.push({dist[y.f],y.f});
    		}
    	}
    }
};

Dijkstra<100> D;

int main() {
	F0R(i,100) F0R(j,100) if (rand() % 10 == 0) D.adj[i].pb({j,rand() % 10+1});
	D.gen();
	F0R(i,100) cout << D.dist[i] << "\n";
}
