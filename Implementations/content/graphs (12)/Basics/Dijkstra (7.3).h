/**
 * Description: shortest path
 * Source: own
 * Verification: https://open.kattis.com/problems/shortestpath1
 */

template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;
template<class T> T poll(pqg<T>& x) {
	T y = x.top(); x.pop(); return y; }

template<class C, int SZ> struct Dijkstra {
	C dist[SZ];
	vector<pair<int,C>> adj[SZ];
	void addEdge(int u, int v, C cost) {
		adj[u].pb({v,cost}); // adj[v].pb({u,cost}); if undirected
	}
	void init(int N, int st) {
		fill_n(dist,N,numeric_limits<C>::max());
		pqg<pair<C,int>> q; q.push({dist[st] = 0,st});
		while (sz(q)) {
			auto x = poll(q); if (dist[x.s] < x.f) continue;
			trav(y,adj[x.s]) if (ckmin(dist[y.f],x.f+y.s))
				q.push({dist[y.f],y.f});
		}
	}
};