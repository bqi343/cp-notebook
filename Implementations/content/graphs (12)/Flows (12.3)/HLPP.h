/**
 * Description: Quickly calculate max flow
 * Source: https://gist.github.com/Chillee/ad2110fc17af453fb6fc3357a78cfd28#file-hlpp-cpp
 * Verification: https://www.spoj.com/problems/FASTFLOW/
 */

template <int SZ> struct HLPP {
	typedef ll F; // flow type
	struct Edge { int to, rev; F f; };
	const F INF = numeric_limits<F>::max();
	
	int N,s,t;
	vector<Edge> adj[SZ];
	void ae(int u, int v, F cap) {
		assert(cap >= 0); // don't try smth dumb
		Edge a{v, sz(adj[v]), cap}, b{u, sz(adj[u]), 0};
		adj[u].pb(a), adj[v].pb(b);
	}

	vi lst[SZ], gap[SZ];
	F excess[SZ];
	int highest, height[SZ], cnt[SZ], work;
	void updHeight(int v, int nh) {
		work++;
		if (height[v] != N) cnt[height[v]]--;
		height[v] = nh;
		if (nh == N) return;
		cnt[nh]++, highest = nh;
		gap[nh].pb(v);
		if (excess[v] > 0) lst[nh].pb(v);
	}
	void globalRelabel() {
		work = 0;
		F0R(i,N) height[i] = N, cnt[i] = 0;
		F0R(i,highest) lst[i].clear(), gap[i].clear();
		height[t] = 0;
		queue<int> q({t});
		while (sz(q)) {
			int v = q.ft; q.pop();
			each(e,adj[v])
				if (height[e.to] == N && adj[e.to][e.rev].f > 0)
					q.push(e.to), updHeight(e.to, height[v] + 1);
			highest = height[v];
		}
	}
	void push(int v, Edge& e) {
		if (excess[e.to] == 0) lst[height[e.to]].pb(e.to);
		F df = min(excess[v], e.f);
		e.f -= df, adj[e.to][e.rev].f += df;
		excess[v] -= df, excess[e.to] += df;
	}
	void discharge(int v) {
		int nh = N;
		each(e,adj[v]) {
			if (e.f > 0) {
				if (height[v] == height[e.to] + 1) {
					push(v, e);
					if (excess[v] <= 0) return;
				} else ckmin(nh,height[e.to]+1);
			}
		}
		if (cnt[height[v]] > 1) updHeight(v, nh);
		else {
			FOR(i,height[v],highest+1) {
				each(j,gap[i]) updHeight(j, N);
				gap[i].clear();
			}
		}
	}
	F maxFlow(int _N, int _s, int _t) {
		N = _N, s = _s, t = _t; if (s == t) return -1;
		F0R(i,N) excess[i] = 0;
		excess[s] = INF, excess[t] = -INF;
		globalRelabel();
		each(e,adj[s]) push(s,e);
		for (; highest >= 0; highest--) 
			while (sz(lst[highest])) {
				int v = lst[highest].bk;
				lst[highest].pop_back();
				discharge(v);
				if (work > 4*N) globalRelabel();
			}
		return excess[t]+INF;
	}
};
