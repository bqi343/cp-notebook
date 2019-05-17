/**
 * Sources: Dhruv Rohatgi, Eric Zhang,
 *           https://sites.google.com/site/kc97ble
 *           /container/splay-tree/splaytree-cpp-3
 * Verification: SPOJ DYNACON1, DYNALCA, Balanced Tokens
 */

typedef struct snode* sn;

struct snode {
    //////// VARIABLES
    int val; // value in node 
    int sum, mn, mx; // sum of values in subtree, min and max prefix sum 
    sn p, c[2]; // parent, children
    bool flip = 0; 
    
    snode(int v) {
        p = c[0] = c[1] = NULL;
        val = v; calc();
    }
    
    friend int getSum(sn x) { return x?x->sum:0; }
    friend int getMn(sn x) { return x?x->mn:0; }
    friend int getMx(sn x) { return x?x->mx:0; }
    
    //////// SPLAY TREE OPERATIONS
    void prop() {
        if (!flip) return;
        swap(c[0],c[1]); tie(mn,mx) = mp(sum-mx,sum-mn);
        F0R(i,2) if (c[i]) c[i]->flip ^= 1;
        flip = 0; 
    }
    void calc() { 
        F0R(i,2) if (c[i]) c[i]->prop();
        int s0 = getSum(c[0]), s1 = getSum(c[1]); sum = s0+val+s1;
        mn = min(getMn(c[0]),s0+val+getMn(c[1]));
        mx = max(getMx(c[0]),s0+val+getMx(c[1]));
    }
    int dir() {
        if (!p) return -2;
        F0R(i,2) if (p->c[i] == this) return i;
        return -1;
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
            if (dir() == p->dir()) p->rot();
            else rot();
            rot();
        }
        if (!isRoot()) p->prop(), prop(), rot();
        prop();
    }

    //////// LINK CUT TREE BASE OPERATIONS
    void access() { // bring this to top of tree, left subtree of this is now path to root
        for (sn v = this, pre = NULL; v; v = v->p) {
            v->splay(); v->c[1] = pre; v->calc();
            pre = v;
        }
        splay(); assert(!c[1]);
    }
    void makeRoot() { access(); flip ^= 1; }
    void set(int v) { splay(); val = v; calc(); } // change val
    
    //////// LINK CUT TREE QUERIES
    friend bool connected(sn x, sn y) {
        if (x == y) return 1;
        x->access(); y->access(); return x->p;
    }
    friend sn lca(sn a, sn b) {
        if (a == b) return a;
        if (!connected(a,b)) return NULL;
        a->splay(); return a->p ? a->p : a;
    }
    friend int balanced(sn x, sn y) { 
        x->makeRoot(); y->access(); 
        return y->sum-2*y->mn;
    }
    
    //////// LINK CUT TREE MODIFICATIONS
    friend bool link(sn x, sn y) { // make y parent of x
        if (connected(x,y)) return 0;
        x->makeRoot(); x->p = y; return 1;
    }
    friend bool cut(sn x, sn y) {
        x->makeRoot(); y->access(); 
        if (y->c[0] != x || x->c[0] || x->c[1]) return 0;
        x->p = y->c[0] = NULL; y->calc(); return 1; // I think calc is redundant as it will be called elsewhere anyways
    }
};