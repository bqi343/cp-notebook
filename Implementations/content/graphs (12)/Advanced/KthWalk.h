/** 
 * Description: $K$-th shortest walk from \texttt{src} to \texttt{des} in digraph. 
 	* All edge weights must be non-negative.
 * Time: O((M+N)\log N+K\log K)
 * Memory: O((M+N)\log N+K)
 * Source: https://judge.yosupo.jp/submission/11843
 * Verification: https://judge.yosupo.jp/problem/k_shortest_walk
 */

#include "LeftistHeap.h"

int N,M,src,des,K;

ph cand[MX];
vector<array<int,3>> adj[MX], radj[MX];
pi pre[MX];
ll dist[MX];

struct state {
	int vert; ph p; ll cost;
	bool operator<(const state& s) const { return cost > s.cost; }
};
priority_queue<state> ans;

void genHeaps() {
	F0R(i,N) dist[i] = INF, pre[i] = {-1,-1};
	priority_queue<T,vector<T>,greater<T>> pq;
	auto ad = [&](int a, ll b, pi ind) {
		if (dist[a] <= b) return;
		pre[a] = ind; pq.push({dist[a] = b,a});
	};
	ad(des,0,{-1,-1});
	vi seq; // reachable vertices in order of dist
	while (sz(pq)) {
		auto a = pq.top(); pq.pop(); 
		if (a.f > dist[a.s]) continue;
		seq.pb(a.s); each(t,radj[a.s]) ad(t[0],a.f+t[1],{t[2],a.s}); // edge index, vert
	}
	each(t,seq) {
		each(u,adj[t]) if (u[2] != pre[t].f && dist[u[0]] != INF) {
			ll cost = dist[u[0]]+u[1]-dist[t]; assert(cost >= 0);
			cand[t] = ins(cand[t],{cost,u[0]});
		}
		if (pre[t].f != -1) cand[t] = meld(cand[t],cand[pre[t].s]);
		if (t == src) {
			ps(dist[t]); K --;
			if (cand[t]) ans.push(state{t,cand[t],dist[t]+cand[t]->v.f});
		}
	}
}

void solve() {
	re(N,M,src,des,K);
	F0R(i,M) {
		int u,v,w; re(u,v,w);
		adj[u].pb({v,w,i}); radj[v].pb({u,w,i}); // vert, weight, label
	}
	genHeaps();
	F0R(i,K) {
		if (!sz(ans)) {
			ps(-1);
			continue;
		}
		auto a = ans.top(); ans.pop();
		int vert = a.vert; 
		ps(a.cost);
		if (a.p->l) ans.push(state{vert,a.p->l,a.cost+a.p->l->v.f-a.p->v.f});
		if (a.p->r) ans.push(state{vert,a.p->r,a.cost+a.p->r->v.f-a.p->v.f});
		int V = a.p->v.s; 
		if (cand[V]) ans.push(state{V,cand[V],a.cost+cand[V]->v.f});
	}
}
