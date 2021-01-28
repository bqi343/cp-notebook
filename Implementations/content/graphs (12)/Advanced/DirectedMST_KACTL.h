/**
 * Description: computes weight of minimum directed spanning tree
 * Time: O(M\log M)
 * Source: KACTL
 	* https://courses.cs.washington.edu/courses/cse490u/17wi/slides/CLE.pdf
 * Verification: https://open.kattis.com/problems/fastestspeedrun
 */

#include "../Fundamentals/DSU (7.6).h"

struct Edge { int a, b; ll w; };
struct Node { /// lazy skew heap node
	Edge key;
	Node *l, *r;
	ll delta;
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
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

ll dmstKACTL(int n, int r, const vector<Edge>& g) {
	DSU dsu; dsu.init(n);
	vector<Node*> heap(n);
	each(e, g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	vi seen(n, -1), path(n); seen[r] = r;
	F0R(s,n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			path[qi++] = u, seen[u] = s;
			if (!heap[u]) return -1;
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			res += e.w, u = dsu.get(e.a);
			if (seen[u] == s) {
				Node* cyc = 0;
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (dsu.unite(u, w));
				u = dsu.get(u);
				heap[u] = cyc, seen[u] = -1;
			}
		}
	}
	return res;
}
