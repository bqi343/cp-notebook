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

    void dis(ps x, int d) { 
        ps y = x->c[d]; 
        if (x) x->c[d] = NULL, recalc(x);
        if (y) y->p = NULL, y->pp = x;
    }
    
    void con(ps x, int d) { setLink(x->pp,x,d); x->pp = NULL; }
    
    void setPref(ps x) { splay(x->pp), dis(x->pp,1), con(x,1); splay(x); }
    
    ps access(ps x) { // x is brought to the root of auxiliary tree
        dis(splay(x),1);
        while (x->pp) setPref(x);
        return x;
    }
    
    //////// UPDATES
    
    ps makeRoot(ps v) { access(v)->flip = 1; return access(v); }
    
    void link(ps v, ps w) { 
        access(w)->pp = makeRoot(v); 
        con(w,0); 
    }
    
    void cut(ps x) { // cut link between x and its parent
        ps y = access(x)->c[0];
        dis(x,0); y->pp = NULL;
    }
    
    //////// QUERIES
    
    int getDepth(ps v) { access(v); return getsz(v->c[0]); }
    
    int getRoot(ps v) { return getExtreme(access(v),0)->id; }
    
    int lca(ps x, ps y) {
        ps root = getExtreme(access(y),0);
        
        dis(splay(x),1);
        auto z = getExtreme(x,0);
        if (z == root) return x->val;
        splay(x);
        
        while (x->pp) {
            auto z = getExtreme(splay(x->pp),0); 
            if (z == root) return x->pp->val;
            setPref(x);
        }
        
        return -1;
    }
};