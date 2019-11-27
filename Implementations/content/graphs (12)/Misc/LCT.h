/**
 * Description: Link-Cut Tree, solves USACO "The Applicant." Given a function 
	* $f(1\ldots N)\to 1\ldots N,$ evaluates $f^b(a)$ for any $a,b.$ Modifications
	* return false in case of failure. Can use \texttt{vir} for subtree size queries. 
 * Time: O(\log N)
 * Source: Dhruv Rohatgi, Eric Zhang,
	* https://sites.google.com/site/kc97ble/container/splay-tree/splaytree-cpp-3
 * Verification: 
	* ekzhang Balanced Tokens
	* Dynamic Tree Test (Easy)
	* https://probgate.org/viewproblem.php?pid=578
 */

typedef struct snode* sn;
struct snode { 
	//////// VARIABLES
	sn p, c[2]; // parent, children
	sn extra; // extra cycle node
	bool flip = 0; // subtree flipped or not
	int val, sz; // value in node, # nodes in subtree
	// int vir = 0; stores sum of virtual children
	snode(int v) {
		p = c[0] = c[1] = NULL;
		val = v; calc();
	}
	friend int getSz(sn x) { return x?x->sz:0; }
	void prop() { // lazy prop
		if (!flip) return;
		swap(c[0],c[1]); F0R(i,2) if (c[i]) c[i]->flip ^= 1;
		flip = 0; 
	}
	void calc() { // recalc vals
		F0R(i,2) if (c[i]) c[i]->prop();
		sz = 1+getSz(c[0])+getSz(c[1]);
	}
	//////// SPLAY TREE OPERATIONS
	int dir() {
		if (!p) return -2;
		F0R(i,2) if (p->c[i] == this) return i;
		return -1; // p is path-parent pointer,
		// so not in current splay tree
	}
	bool isRoot() { return dir() < 0; } 
	// test if root of current splay tree
	friend void setLink(sn x, sn y, int d) {
		if (y) y->p = x;
		if (d >= 0) x->c[d] = y;
	}
	void rot() { // assume p and p->p propagated
		assert(!isRoot()); int x = dir(); sn pa = p;
		setLink(pa->p, this, pa->dir());
		setLink(pa, c[x^1], x);
		setLink(this, pa, x^1);
		pa->calc(); calc();
	}
	void splay() {
		while (!isRoot() && !p->isRoot()) {
			p->p->prop(), p->prop(), prop();
			dir() == p->dir() ? p->rot() : rot();
			rot();
		}
		if (!isRoot()) p->prop(), prop(), rot();
		prop();
	}
	//////// LINK CUT TREE BASE OPERATIONS
	void access() { // bring this to top of tree
		for (sn v = this, pre = NULL; v; v = v->p) {
			v->splay(); 
			// if (pre) v->vir -= pre->sz;
			// if (v->c[1]) v->vir += v->c[1]->sz;
			v->c[1] = pre; v->calc();
			pre = v;
			// v->sz should remain the same if using vir
		}
		splay(); // left subtree of this is now path to root
		assert(!c[1]); // right subtree is empty
	}
	void makeRoot() { access(); flip ^= 1; }
	void set(int v) { splay(); val = v; calc(); } // change value in node
	// splay suffices instead of access because it doesn't affect values in nodes above it
	//////// LINK CUT TREE QUERIES
	friend sn lca(sn x, sn y) {
		if (x == y) return x;
		x->access(), y->access(); if (!x->p) return NULL; 
		// access at y did not affect x
		// so they must not be connected
		x->splay(); return x->p ? x->p : x;
	}
	friend bool connected(sn x, sn y) { return lca(x,y); } 
	// LCA is null if not connected
	int distRoot() { access(); return getSz(c[0]); } 
	// # nodes above
	sn getRoot() { // get root of LCT component
		access(); auto a = this; 
		while (a->c[0]) a = a->c[0], a->prop();
		a->access(); return a;
	}
	sn dfs(int b) {
		int z = getSz(c[0]);
		if (b < z) return c[0]->dfs(b);
		if (b == z) { access(); return this; }
		return c[1]->dfs(b-z-1);
	}
	sn getPar(int b) { // get b-th parent
		access(); 
		b = getSz(c[0])-b; assert(b >= 0);
		auto a = this;
		while (1) {
			int z = getSz(a->c[0]);
			if (b == z) { a->access(); return a; }
			if (b < z) a = a->c[0];
			else a = a->c[1], b -= z+1;
			a->prop();
		}
	}
	//////// LINK CUT TREE MODIFICATIONS
	friend bool link(sn x, sn y) { // make x parent of y
		if (connected(x,y)) return 0; // don't induce cycle
		y->access(); assert(!y->c[0]); 
		// or y->makeRoot() if you want to ensure link succeeds
		y->p = x; 
		// x->access(); x->sz += y->sz; x->vir += y->sz;
		return 1;
	}
	friend bool cut(sn y) { // cut y from its parent
		y->access(); if (!y->c[0]) return 0;
		y->c[0]->p = NULL; y->c[0] = NULL;
		y->calc(); return 1;
	}
	friend bool cut(sn x, sn y) { // if x, y adjacent in tree
		x->makeRoot(); y->access(); 
		if (y->c[0] != x || x->c[0] || x->c[1]) return 0; 
		// splay tree with y should not contain anything besides x
		assert(cut(y)); return 1;
	}
};

sn LCT[MX];
void setNex(sn a, sn b) { // set f[a] = b
	if (connected(a,b)) a->extra = b;
	else assert(link(b,a));
}
void delNex(sn a) { // set f[a] = NULL
	auto t = a->getRoot();
	if (t == a) { t->extra = NULL; return; }
	assert(cut(a)); assert(t->extra);
	if (!connected(t,t->extra)) {
		assert(link(t->extra,t)); t->extra = NULL; }
}
sn getPar(sn a, int b) { // get f^b[a]
	int d = a->distRoot();
	if (b <= d) return a->getPar(b);
	b -= d+1; auto r = a->getRoot()->extra; assert(r);
	d = r->distRoot()+1; 
	return r->getPar(b%d);
}