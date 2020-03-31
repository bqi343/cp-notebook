/**
 * Description: shortest path
 * Source: own
 * Verification: https://open.kattis.com/problems/shortestpath1
 */

template<class C, bool directed> struct Dijkstra {
	int SZ; vector<C> dist; 
	vector<vector<pair<int,C>>> adj;
	void init(int _SZ) { SZ = _SZ; adj.rsz(SZ); }
	void ae(int u, int v, C cost) {
		adj[u].pb({v,cost}); if (!directed) adj[v].pb({u,cost}); }
	void gen(int st) {
		dist = vector<C>(SZ,numeric_limits<C>::max());
		typedef pair<C,int> T; priority_queue<T,vector<T>,greater<T>> pq; 
		auto ad = [&](int a, int b) {
			if (dist[a] <= b) return;
			pq.push({dist[a] = b,a});
		}; ad(st,0);
		while (sz(pq)) {
			auto x = pq.top(); pq.pop(); if (dist[x.s] < x.f) continue;
			trav(y,adj[x.s]) ad(y.f,x.f+y.s);
		}
	}
};