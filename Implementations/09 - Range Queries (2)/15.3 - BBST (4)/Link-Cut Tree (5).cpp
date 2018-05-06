/**
* Sources: Dhruv Rohatgi,
*           https://sites.google.com/site/kc97ble
*           /container/splay-tree/splaytree-cpp-3
* Usage: SPOJ DYNACON1, DYNALCA
*/

template<int SZ> struct LCT {
    // [splay tree template]
    
    //////// LINK CUT TREE
    
    snode* S[SZ];
    LCT () { F0R(i,SZ) S[i] = new snode(i); }

    void dis(snode* x, int d) { 
        snode* y = x->c[d]; 
        if (x) x->c[d] = NULL, x->recalc();
        if (y) y->p = NULL, y->pp = x;
    }
    
    void con(snode* x, int d) { 
        setLink(x->pp,x,d); x->pp = NULL; 
    }
    
    snode* getExtreme(snode* x, int d) {
        prop(x);
        if (x->c[d]) return getExtreme(x->c[d],d);
        return splay(x);
    }
    
    void setPref(snode* x) { splay(x->pp), dis(x->pp,1), con(x,1); splay(x); }
    
    snode* access(snode* x) { // v is brought to the root of auxiliary tree
        dis(splay(x),1);
        while (x->pp) setPref(x);
        return x;
    }
    
    //////// UPDATES
    
    snode* makeRoot(snode* v) { access(v)->flip = 1; return access(v); }
    
    void link(snode* v, snode* w) { 
        access(w)->pp = makeRoot(v); 
        con(w,0); 
    }
    
    void cut(snode* x) { // cut link between v and par[v]
        snode* y = access(x)->c[0];
        dis(x,0); y->pp = NULL;
    }
    
    //////// QUERIES
    
    int getDepth(snode* v) { access(v); return getNum(v->c[0]); }
    
    int getXo(snode* v) { access(v); return v->val^(v->c[0]?v->c[0]->xo:0); }
    
    int findRoot(snode* v) { return getExtreme(access(v),0)->id; }
    
    int lca(snode* x, snode* y) {
        snode* root = getExtreme(access(y),0);
        
        dis(splay(x),1);
        auto z = getExtreme(x,0);
        if (z == root) return x->id;
        splay(x);
        
        while (x->pp) {
            auto z = getExtreme(splay(x->pp),0); 
            if (z == root) return x->pp->id;
            setPref(x);
        }
        
        return -1;
    }
};
