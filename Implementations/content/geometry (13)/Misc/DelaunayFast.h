/**
 * Description: Fast Delaunay triangulation assuming no duplicates and not 
 	* all points collinear (in latter case, result will be empty). Should 
 	* work for doubles as well, though there may be precision issues in 'circ'.
	* Returns triangles in ccw order. Each circumcircle will contain none 
	* of the input points. If coordinates are ints at most $B$ then \texttt{T} 
	* should be large enough to support ints on the order of $B^4$.
 * Time: O(N\log N)
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/cco08p6
 */

#include "../Primitives/Point.h"

// using T = ll;
using lll = __int128; // (can be ll if coords are < 2e4)
bool inCircle(P p, P a, P b, P c) {
	a -= p, b -= p, c -= p; // assert(cross(a,b,c)>0);
	lll x = (lll)norm(a)*cross(b,c)+(lll)norm(b)*cross(c,a)
			+(lll)norm(c)*cross(a,b);
	return x*(cross(a,b,c)>0?1:-1) > 0;
}

P arb(LLONG_MAX,LLONG_MAX); // not equal to any other point
typedef struct Quad* Q;
struct Quad {
	bool mark; Q o, rot; P p;
	P F() { return r()->p; }
	Q r() { return rot->rot; }
	Q prev() { return rot->o->rot; }
	Q next() { return r()->prev(); }
};
Q makeEdge(P orig, P dest) {
	Q q[] = {new Quad{0,0,0,orig}, new Quad{0,0,0,arb},
			 new Quad{0,0,0,dest}, new Quad{0,0,0,arb}};
	F0R(i,4) q[i]->o = q[-i & 3], q[i]->rot = q[(i+1) & 3];
	return *q;
}
void splice(Q a, Q b) { swap(a->o->rot->o, b->o->rot->o); swap(a->o, b->o); }
Q connect(Q a, Q b) {
	Q q = makeEdge(a->F(), b->p);
	splice(q, a->next()); splice(q->r(), b);
	return q;
}
pair<Q,Q> rec(const vP& s) {
	if (sz(s) <= 3) {
		Q a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.bk);
		if (sz(s) == 2) return { a, a->r() };
		splice(a->r(), b);
		auto side = cross(s[0], s[1], s[2]);
		Q c = side ? connect(b, a) : 0;
		return {side < 0 ? c->r() : a, side < 0 ? c : b->r() };
	}

#define H(e) e->F(), e->p
#define valid(e) (cross(e->F(),H(base)) > 0)
	Q A, B, ra, rb;
	int half = sz(s) / 2;
	tie(ra, A) = rec({all(s)-half});
	tie(B, rb) = rec({sz(s)-half+all(s)});
	while ((cross(B->p,H(A)) < 0 && (A = A->next())) ||
		   (cross(A->p,H(B)) > 0 && (B = B->r()->o)));
	Q base = connect(B->r(), A);
	if (A->p == ra->p) ra = base->r();
	if (B->p == rb->p) rb = base;

#define DEL(e, init, dir) Q e = init->dir; if (valid(e)) \
		while (inCircle(e->dir->F(), H(base), e->F())) { \
			Q t = e->dir; \
			splice(e, e->prev()); \
			splice(e->r(), e->r()->prev()); \
			e = t; \
		}
	while (1) {
		DEL(LC, base->r(), o);	DEL(RC, base, prev());
		if (!valid(LC) && !valid(RC)) break;
		if (!valid(LC) || (valid(RC) && inCircle(H(RC), H(LC))))
			base = connect(RC, base->r());
		else base = connect(base->r(), LC->r());
	}
	return {ra, rb};
}
vector<array<P,3>> triangulate(vP pts) {
	sort(all(pts)); assert(unique(all(pts)) == end(pts)); // no duplicates
	if (sz(pts) < 2) return {};
	Q e = rec(pts).f; vector<Q> q = {e};
	while (cross(e->o->F(), e->F(), e->p) < 0) e = e->o;
#define ADD { Q c = e; do { c->mark = 1; pts.pb(c->p); \
	q.pb(c->r()); c = c->next(); } while (c != e); }
	ADD; pts.clear();
	int qi = 0; while (qi < sz(q)) if (!(e = q[qi++])->mark) ADD;
	vector<array<P,3>> ret(sz(pts)/3); 
	F0R(i,sz(pts)) ret[i/3][i%3] = pts[i];
	return ret;
}
