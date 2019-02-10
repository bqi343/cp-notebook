/**
 * Sources: Dhruv Rohatgi,
 *           https://sites.google.com/site/kc97ble
 *           /container/splay-tree/splaytree-cpp-3
 * Verification: SPOJ DYNACON1, DYNALCA
 */

using namespace splayTree;

template<int SZ> struct LCT {
    ps S[SZ];
    LCT () { F0R(i,SZ) S[i] = new snode(i); }

    // disconnect x from d-th child
    void dis(ps x, int d) { 
        ps y = x->c[d]; 
        if (x) x->c[d] = NULL, recalc(x);
        if (y) { y->p = NULL; if (d) y->pp = x; }
    }
    // set x to be child of pp
    void makeChild(ps x) { setLink(x->pp,x,1); x->pp = NULL; } 
    // unlink x->pp from its preferred child, then set x to be preferred child 
    void setPref(ps x) { splay(x->pp), dis(x->pp,1), makeChild(x), splay(x); } 
    // x is brought to the root of auxiliary tree
    ps access(ps x) { dis(splay(x),1); while (x->pp) setPref(x); return x; }
    
    //////// UPDATES
    
    ps makeRoot(ps v) { access(v)->flip = 1; return access(v); }
    // make y the parent of x
    void link(ps x, ps y) { makeRoot(x)->pp = y; }
    // cut link between x and its parent
    void cut(ps x) { dis(access(x),0); }
    
    //////// QUERIES
    
    int getDepth(ps x) { access(x); return getsz(x->c[0]); }
    ps getRoot(ps x) { return farthest(access(x),0); }
    ps lca(ps x, ps y) {
        ps root = getRoot(y); 
        if (farthest(splay(x),0) == root) return x;
        while (splay(x)->pp) {
            if (farthest(splay(x->pp),0) == root) return x->pp;
            setPref(splay(x));
        }
        return NULL;
    }
};