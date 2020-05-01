/**
 * Description: nearest neighbor to point and squared dist
 * Time: Insertion and find nearest neighbor are $O(\log N)$ on 
 	* average for randomly distributed points.
 * Source: KACTL, Stanford
 	* https://en.wikipedia.org/wiki/K-d_tree
 * Verification: https://open.kattis.com/problems/closestpair1
 */

#include "Point.h"

struct Node {
	P pt; // if this is a leaf, the single point in it
	T x0 = INF, x1 = -INF, y0 = INF, y1 = -INF; // bounds
	Node *f = 0, *s = 0;
	T distance(const P& p) { // min squared dist to point p
		T x = min(max(p.f,x0),x1), y = min(max(p.s,y0),y1); 
		return norm(P(x,y)-p); }
	Node(vP&& vp) : pt(vp[0]) {
		for (P p : vp) { ckmin(x0,p.f), ckmax(x1,p.f);
			ckmin(y0,p.s), ckmax(y1,p.s); }
		if (sz(vp) > 1) { // split on x if the box is 
			// wider than high (not best heuristic...)
			if (x1-x0 >= y1-y0) sort(all(vp));
			else sort(all(vp),[](P a,P b) { return a.s < b.s; });
			// divide by taking half the array for each child (not
			// best performance with many duplicates in the middle)
			int half = sz(vp)/2;
			f = new Node({begin(vp),begin(vp)+half});
			s = new Node({half+all(vp)});
		}
	}
};
struct KDtree {
	Node* root; KDtree(const vP& vp):root(new Node({all(vp)})){}
	pair<T,P> search(Node *node, const P& p) {
		if (!node->f) { // should not find the point itself
			if (p == node->pt) return {INF, P()};
			return {norm(p-node->pt), node->pt}; }
		Node *f = node->f, *s = node->s;
		T bf = f->distance(p), bs = s->distance(p);
		if (bf > bs) swap(bs,bf), swap(f,s);
		// search closest side f, other side if needed
		auto best = search(f,p); 
		if (bs < best.f) ckmin(best,search(s,p));
		return best;
	}
	pair<T,P> nearest(const P& p) { return search(root,p); }
};