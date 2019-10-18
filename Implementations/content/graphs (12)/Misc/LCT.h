/**
 * Description: Link-Cut Tree, use \texttt{vir} for subtree size queries
 * Time: O(\log N)
 * Source: Dhruv Rohatgi, Eric Zhang,
	* https://sites.google.com/site/kc97ble/container/splay-tree/splaytree-cpp-3
 * Verification: Balanced Tokens, Dynamic Tree Test (Easy)
 */

typedef struct snode* sn;

struct snode {
	//////// VARIABLES
	sn p, c[2]; // parent, children
	int val; // value in node 
	int sum, mn, mx; // sum of values in subtree, min and max prefix sum 
	bool flip = 0; 
	// int vir = 0; stores sum of virtual children
	
	snode(int v) {
		p = c[0] = c[1] = NULL;
		val = v; calc();
	}
	
	friend int getSum(sn x) { return x?x->sum:0; }
	friend int getMn(sn x) { return x?x->mn:0; }
	friend int getMx(sn x) { return x?x->mx:0; }
	
	void prop() {
		if (!flip) return;
		swap(c[0],c[1]); tie(mn,mx) = mp(sum-mx,sum-mn);
		F0R(i,2) if (c[i]) c[i]->flip ^= 1;
		flip = 0; 
	}
	void calc() { 
		F0R(i,2) if (c[i]) c[i]->prop();
		int s0 = getSum(c[0]), s1 = getSum(c[1]); sum = s0+val+s1; // +vir
		mn = min(getMn(c[0]),s0+val+getMn(c[1]));
		mx = max(getMx(c[0]),s0+val+getMx(c[1]));
	}
	
	//////// SPLAY TREE OPERATIONS
	int dir() {
		if (!p) return -2;
		F0R(i,2) if (p->c[i] == this) return i;
		return -1; // p is path-parent pointer, not in current splay tree
	}
	bool isRoot() { return dir() < 0; }
	
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
		splay(); assert(!c[1]); // left subtree of this is now path to root, right subtree is empty
	}
	void makeRoot() { access(); flip ^= 1; }
	void set(int v) { splay(); val = v; calc(); } // change value in node, splay suffices instead of access because it doesn't affect values in nodes above it
	
	//////// LINK CUT TREE QUERIES
	friend sn lca(sn x, sn y) {
		if (x == y) return x;
		x->access(), y->access(); if (!x->p) return NULL; // access at y did not affect x, so they must not be connected
		x->splay(); return x->p ? x->p : x;
	}
	friend bool connected(sn x, sn y) { return lca(x,y); }
	friend int balanced(sn x, sn y) { 
		x->makeRoot(); y->access(); 
		return y->sum-2*y->mn;
	}
	
	//////// LINK CUT TREE MODIFICATIONS
	friend bool link(sn x, sn y) { // make x parent of y
		if (connected(x,y)) return 0; // don't induce cycle
		y->makeRoot(); y->p = x; 
		// x->access(); x->sz += y->sz; x->vir += y->sz;
		return 1; // success!
	}
	friend bool cut(sn x, sn y) { // x is originally parent of y
		x->makeRoot(); y->access(); 
		if (y->c[0] != x || x->c[0] || x->c[1]) return 0; // splay tree with y should not contain anything else besides x
		x->p = y->c[0] = NULL; y->calc(); return 1; // calc is redundant as it will be called elsewhere anyways?
	}
};
