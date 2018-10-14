/**
* Description: Treap alternative
* Source: see LCT
* Verification: ~
*/

namespace splayTree {
    typedef struct snode* ps;

    struct snode {
        int val; ps p, pp, c[2]; // essential
        int sz; // # nodes in subtree
        bool flip; // range flip 

        snode (int _val) { 
            val = _val; c[0] = c[1] = p = pp = NULL; 
            sz = 1; flip = 0;
        }
    };

    int getsz(ps x) { return x?x->sz:0; }
    int getDir(ps x, ps y) { return x?(x->c[1] == y):-1; }

    void trav(ps x, vi& v) {
        if (!x) return;
        trav(x->c[0],v); v.pb(x->val); trav(x->c[1],v);
    }
    
    ps recalc(ps x) {
        x->sz = 1+getsz(x->c[0])+getsz(x->c[1]);
        return x;
    }

    void setLink(ps x, ps y, int d) { // x propagated
        if (x) x->c[d] = y, recalc(x);
        if (y) y->p = x;
    }

    void prop(ps x) {
        if (!x || !x->flip) return; 
        swap(x->c[0],x->c[1]);
        if (x->c[0]) x->c[0]->flip ^= 1;
        if (x->c[1]) x->c[1]->flip ^= 1;
        x->flip = 0;
    }

    void pushDown(ps x) {
        if (!x) return;
        if (x->p) pushDown(x->p);
        prop(x);
    }

    void rot(ps x, int d) { // precondition: x & parents propagated
        snode *y = x->c[d], *z = x->p;
        prop(y);
        setLink(x, y->c[d^1], d);
        setLink(y, x, d^1);
        setLink(z, y, getDir(z, x));
        y->pp = x->pp; x->pp = NULL;
    }

    ps splay(ps x) {
        pushDown(x);
        while (x && x->p) {
            ps y = x->p, z = y->p;
            int dy = getDir(y, x), dz = getDir(z, y);
            if (!z) rot(y, dy);
            else if (dy == dz) rot(z, dz), rot(y, dy);
            else rot(y, dy), rot(z, dz);
        }
        return x;
    }
    
    ps getExtreme(ps x, int d) { // get leftmost or rightmost node
        prop(x);
        if (x->c[d]) return getExtreme(x->c[d],d);
        return splay(x);
    }
}

using namespace splayTree;