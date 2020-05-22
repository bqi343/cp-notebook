/**
 * Description: Easy BBST. Use split and merge to implement insert and delete.
 * Time: O(\log N)
 * Source: https://cp-algorithms.com/data_structures/treap.html + others. Also consider
 	* https://codeforces.com/contest/1340/submission/77861280 (no pointers -> faster)
 	* https://codeforces.com/contest/1340/submission/77852254 (shared_ptr -> destroyed when nothing refers to it)
 * Verification: http://www.spoj.com/problems/ORDERSET/
 */

typedef struct tnode* pt;
struct tnode {
	int pri, val; pt c[2]; // essential
	int sz; ll sum; // for range queries
	bool flip = 0; // lazy update
	tnode (int _val) {
		pri = rng(); sum = val = _val; 
		sz = 1; c[0] = c[1] = NULL;
	}
	~tnode() { F0R(i,2) delete c[i]; } // assume no sharing of data
};
int getsz(pt x) { return x?x->sz:0; }
ll getsum(pt x) { return x?x->sum:0; }
pt prop(pt x) { // lazy propagation
	if (!x || !x->flip) return x;	
	swap(x->c[0],x->c[1]);
	x->flip = 0; F0R(i,2) if (x->c[i]) x->c[i]->flip ^= 1;
	return x;
}
pt calc(pt x) {
	pt a = x->c[0], b = x->c[1];
	assert(!x->flip); prop(a), prop(b);
	x->sz = 1+getsz(a)+getsz(b);
	x->sum = x->val+getsum(a)+getsum(b);
	return x;
}
void tour(pt x, vi& v) { // print values of nodes, 
	if (!x) return; // inorder traversal
	prop(x); tour(x->c[0],v); v.pb(x->val); tour(x->c[1],v);
}
pair<pt,pt> split(pt t, int v) { // >= v goes to the right
	if (!t) return {t,t};
	prop(t);
	if (t->val >= v) {
		auto p = split(t->c[0], v); t->c[0] = p.s;
		return {p.f,calc(t)};
	} else {
		auto p = split(t->c[1], v); t->c[1] = p.f;
		return {calc(t),p.s};
	}
}
pair<pt,pt> splitsz(pt t, int sz) { // sz nodes go to left
	if (!t) return {t,t};
	prop(t);
	if (getsz(t->c[0]) >= sz) {
		auto p = splitsz(t->c[0],sz); t->c[0] = p.s;
		return {p.f,calc(t)};
	} else {
		auto p=splitsz(t->c[1],sz-getsz(t->c[0])-1); t->c[1]=p.f;
		return {calc(t),p.s};
	}
}
pt merge(pt l, pt r) { // merge treaps, keys in left < keys in right
	if (!l || !r) return l?:r;
	prop(l), prop(r); pt t;
	if (l->pri > r->pri) l->c[1] = merge(l->c[1],r), t = l;
	else r->c[0] = merge(l,r->c[0]), t = r;
	return calc(t);
}
pt ins(pt x, int v) { // insert v
	auto a = split(x,v), b = split(a.s,v+1);
	return merge(a.f,merge(new tnode(v),b.s)); }
pt del(pt x, int v) { // delete v
	auto a = split(x,v), b = split(a.s,v+1);
	return merge(a.f,b.s); }