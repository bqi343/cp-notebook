/**
 * Description: Persistent meldable heap.
 * Time: O(\log N) per meld
 * Memory: O(\log N) per meld
 * Source:
 	* https://judge.yosupo.jp/submission/11843
 	* https://en.wikipedia.org/wiki/Leftist_tree
 * Verification: See Kth Walk
 */

typedef pair<ll,int> T;
typedef struct heap* ph;
struct heap { // min heap
	ph l = NULL, r = NULL;
	int s = 0; T v; // s: path to leaf
	heap(T _v):v(_v) {}
};

ph meld(ph p, ph q) {
	if (!p || !q) return p?:q;
	if (p->v > q->v) swap(p,q);
	ph P = new heap(*p); P->r = meld(P->r,q);
	if (!P->l || P->l->s < P->r->s) swap(P->l,P->r);
	P->s = (P->r?P->r->s:0)+1; return P;
}
ph ins(ph p, T v) { return meld(p, new heap(v)); }
ph pop(ph p) { return meld(p->l,p->r); }