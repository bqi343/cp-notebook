/**
 * Description: Chu-Liu-Edmonds algorithm. Computes minimum weight directed 
 	* spanning tree rooted at $r$, edge from $par[i]\to i$ for all $i\neq r.$
 	* Use DSU with rollback if need to return edges.
 * Time: O(M\log M)
 * Source: KACTL
 	* https://courses.cs.washington.edu/courses/cse490u/17wi/slides/CLE.pdf
 * Verification: 
 	* https://open.kattis.com/problems/fastestspeedrun
 	* https://codeforces.com/problemset/problem/240/E
 */

#include "../DSU/DSUrb (15.5).h"

struct Edge { int a, b; ll w; };
struct Node { // lazy skew heap node
	Edge key; Node *l, *r; ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, a->r = merge(b, a->r));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

pair<ll,vi> dmst(int n, int r, const vector<Edge>& g) {
	DSUrb dsu; dsu.init(n); 
	vector<Node*> heap(n); // store edges entering each vertex 
	// in increasing order of weight
	each(e,g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0; vi seen(n,-1); seen[r] = r; 
	vpi in(n,{-1,-1}); // edge entering each vertex in MST
	vector<pair<int,vector<Edge>>> cycs;
	F0R(s,n) {
		int u = s, w;
		vector<pair<int,Edge>> path; 
		while (seen[u] < 0) {
			if (!heap[u]) return {-1,{}};
			seen[u] = s;
			Edge e = heap[u]->top(); path.pb({u,e}); 
			heap[u]->delta -= e.w, pop(heap[u]);
			res += e.w, u = dsu.get(e.a); 
			if (seen[u] == s) { // found cycle, contract
				Node* cyc = 0; cycs.eb();
				do {
					cyc = merge(cyc, heap[w = path.bk.f]);
					cycs.bk.s.pb(path.bk.s);
					path.pop_back(); 
				} while (dsu.unite(u,w));
				u = dsu.get(u); heap[u] = cyc, seen[u] = -1;
				cycs.bk.f = u;
			}
		}
		each(t,path) in[dsu.get(t.s.b)] = {t.s.a,t.s.b}; 
	} // found path from root to s, done
	while (sz(cycs)) { // expand cycs to restore sol
		auto c = cycs.bk; cycs.pop_back();
		pi inEdge = in[c.f];
		each(t,c.s) dsu.rollback();
		each(t,c.s) in[dsu.get(t.b)] = {t.a,t.b};
		in[dsu.get(inEdge.s)] = inEdge;
	}
	vi par(n); F0R(i,n) par[i] = in[i].f; 
	// i == r ? in[i].s == -1 : in[i].s == i
	return {res,par};
}
