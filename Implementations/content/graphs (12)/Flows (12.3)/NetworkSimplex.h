/**
 * Description: Min Cost Circulation w/ Supplies and Demands via Network Simplex
 * Time: ?
 * Source: https://codeforces.com/blog/entry/94190?#comment-832221
 * Verification: https://judge.yosupo.jp/problem/min_cost_b_flow
 */

using i128 = __int128_t;
struct NetworkSimplex {
	using Flow = int64_t; using Cost = int64_t; using V_id = int32_t; using E_id = int32_t;
	struct Edge { V_id src, dst; Flow flow, cap; Cost cost; };
	Cost INF = 1; i128 delta = 0;
	int n; V<Flow> B; V<Cost> P; V<Edge> E;
	vi pei, depth; V<set<int>> tree;
	void init(int _n) { n = _n; B.rsz(n+1); pei.assign(n+1,-1);
		depth.rsz(n+1); P.rsz(n+1); tree.rsz(n+1); }
	int ae(V_id a, V_id b, Flow l, Flow u, Cost c) {
		E.pb({a,b,0,u-l,c}); E.pb({b,a,0,0,-c});
		delta += l*c; B[b] += l, B[a] -= l;
		return sz(E)-2;
	}
	void upd(E_id ei) {
		P[E[ei].dst] = P[E[ei].src]+E[ei].cost;
		pei[E[ei].dst] = ei^1;
		depth[E[ei].dst] = 1+depth[E[ei].src];
		dfs(E[ei].dst);
	}
	void dfs(int node) { each(ei,tree[node]) if (ei != pei[node]) upd(ei); }
	// applies cb to a -> b and (tree path b -> a)
	template<class CB> void walk(int ei, CB cb) {
		cb(ei);
		for (V_id a = E[ei].src, b = E[ei].dst; a != b; ) {
			if (depth[a] > depth[b]) cb(pei[a]^1), a = E[pei[a]].dst;
			else cb(pei[b]), b = E[pei[b]].dst;
		}
	}
	i128 solve() {
		const int m = sz(E);
		for (E_id i = 0; i < m; i += 2) INF += abs(E[i].cost);
		F0R(i,n) {
			V_id a = n, b = i; Cost c = B[i];
			if (c < 0) c *= -1, swap(a,b);
			E_id ei = ae(a,b,0,c,-INF);
			tree[a].ins(ei), tree[b].ins(ei^1);
		}
		dfs(n);
		i128 answer = delta;
		E_id ptr = 0;
		const int BLOCK = n/3+1;
		F0R(z,sz(E)/BLOCK+1) {
			pair<Cost,E_id> pin{0,-1};
			for (int t = 0; t < BLOCK; ++t, (++ptr) %= sz(E)) {
				const auto& e = E[ptr];
				if (e.flow < e.cap) ckmin(pin, mp(e.cost+P[e.src]-P[e.dst],ptr));
			}
			auto [cost, ein] = pin; 
			if (cost == 0) continue;
			pair<Cost,E_id> pout{E[ein].cap-E[ein].flow, ein};
			walk(ein,[&](E_id ei) { ckmin(pout, mp(E[ei].cap-E[ei].flow,ei)); });
			auto [flow, eout] = pout;
			walk(ein,[&](E_id ei) { E[ei].flow += flow, E[ei^1].flow -= flow; });
			tree[E[ein].src].ins(ein), tree[E[ein].dst].ins(ein^1);
			tree[E[eout].src].erase(eout), tree[E[eout].dst].erase(eout^1);
			upd(pei[E[eout].src] == eout ? ein : ein^1);
			answer += i128(flow)*cost; // why can't this loop?
			z = -1;
		}
		F0R(i,n) {
			if (E[m+2*i].flow < E[m+2*i].cap) throw 5;
			answer += i128(E[m+2*i].flow)*INF;
		}
		return answer;
	}
};