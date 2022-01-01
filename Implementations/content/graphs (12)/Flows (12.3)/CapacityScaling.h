/**
 * Description: Min Cost Circulation w/ Supplies and Demands via Capacity Scaling
 * Time: O(M^2 log U log M)
 * Source: Own
 * Verification: https://judge.yosupo.jp/problem/min_cost_b_flow
 */

using i128 = __int128_t;
struct CapacityScaling {
	using Flow = int64_t; using Cost = int64_t; using V_id = int32_t; using E_id = int32_t;
	Cost INF = 1; i128 ans_delta = 0;
	struct Edge { V_id src, dst; Flow flow, cap; Cost cost; };
	int N; V<Flow> B; V<V<E_id>> G; V<Cost> P; V<Edge> E;
	V<E_id> pre_edge;
	void init(int _N) { N = _N; B.rsz(N), G.rsz(N+1), P.rsz(N+1), pre_edge.rsz(N+1); }
	E_id ae(V_id a, V_id b, Flow l, Flow u, Cost c) {
		G[a].pb(sz(E)); E.pb(Edge{a,b,0,u-l,c});
		G[b].pb(sz(E)); E.pb(Edge{b,a,0,0,-c});
		ans_delta += l*c; B[a] -= l, B[b] += l;
		return sz(E)-2;
	}
	V_id backtrack(V_id x, Flow delta) { assert(delta > 0);
		while (pre_edge[x] != -1) {
			E[pre_edge[x]].flow += delta;
			assert(E[pre_edge[x]].flow <= E[pre_edge[x]].cap);
			E[pre_edge[x]^1].flow -= delta; 
			x = E[pre_edge[x]].src;
		}
		return x;
	}
	void pin(int x) {
		using T = pair<Cost,int>;
		priority_queue<T,V<T>,greater<T>> pq;
		V<Cost> add(N+1); F0R(i,N+1) add.at(i) = -P.at(i);
		add.at(x) -= 3*INF;
		F0R(i,N+1) pq.push({add[i],i});
		pre_edge[x] = -1;
		while (sz(pq)) {
			auto p = pq.top(); pq.pop();
			if (p.f > add.at(p.s)) continue;
			each(e,G[p.s]) if (E[e].flow < E[e].cap)
				if (ckmin(add.at(E[e].dst),p.f+E[e].cost+P.at(E[e].src)-P.at(E[e].dst))) {
					pre_edge[E[e].dst] = e;
					pq.push({add.at(E[e].dst),E[e].dst});
				}
		}
		F0R(i,N+1) P.at(i) += add.at(i);
	}
	void add_cap(E_id e, Flow delta) { // increase cap by delta, update potentials
		assert(delta > 0);
		if (E[e].flow == E[e].cap) {
			pin(E[e].dst);
			if (P[E[e].src]-P[E[e].dst]+E[e].cost < 0) {
				assert(backtrack(E[e].src,delta) == E[e].dst);
				E[e].flow += delta; E[e^1].flow -= delta;
			}
		}
		E[e].cap += delta;
	}
	i128 solve() {
		const int M = sz(E);
		for (E_id i = 0; i < M; i += 2) INF += abs(E.at(i).cost);
		F0R(i,N) {
			int a = N, b = i; Flow c = B[i];
			if (c < 0) c *= -1, swap(a,b);
			ae(a,b,0,c,-INF);
		}
		V<Flow> caps(sz(E)); 
		Flow max_cap = 1;
		F0R(i,sz(E)) {
			swap(caps[i],E[i].cap);
			ckmax(max_cap,caps[i]);
		}
		Flow delta = 1; while (delta < max_cap) delta *= 2;
		for (; delta; delta /= 2)
			F0R(i,sz(E)) if (caps[i]&delta)
				add_cap(i,delta);
		F0R(i,N) if (E[M+2*i].flow < E[M+2*i].cap) throw 5;
		i128 ans = ans_delta;
		for (E_id i = 0; i < M; i += 2) ans += E.at(i).flow*E.at(i).cost;
		return ans;
	}
};