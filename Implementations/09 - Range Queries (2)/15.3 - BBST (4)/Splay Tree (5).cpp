/**
 * Description: Treap alternative
 * Source: see LCT
 * Verification: ~
 */

namespace splayTree {
    typedef struct snode* sn;

    struct snode {
        int val, sz; // value, # nodes in subtree
        sn p, pp, c[2]; // parent, path-parent (for LCT), children
        bool flip; // for range flip 

        snode (int val) : val(val) { 
            sz = 1;
            p = pp = c[0] = c[1] = NULL; 
            flip = 0;
        }
    };

    int getsz(sn x) { return x ? x->sz : 0; }
    int dir(sn x, sn y) { return x ? (x->c[1] == y) : -1; }
    sn recalc(sn x) {
        x->sz = 1+getsz(x->c[0])+getsz(x->c[1]);
        return x;
    }
    void prop(sn x) {
        if (!x || !x->flip) return; 
        swap(x->c[0],x->c[1]);
        if (x->c[0]) x->c[0]->flip ^= 1;
        if (x->c[1]) x->c[1]->flip ^= 1;
        x->flip = 0;
    }
    void propAnc(sn x) { // propagate all ancestors
        if (!x) return;
        if (x->p) propAnc(x->p);
        prop(x);
    }
    void tour(sn x, vi& v) {
        if (!x) return;
        tour(x->c[0],v); v.pb(x->val); tour(x->c[1],v);
    }

    void setLink(sn x, sn y, int d) { // x propagated
        if (x) x->c[d] = y, recalc(x);
        if (y) y->p = x;
    }
    void rot(sn x, int d) { // precondition: x & parents propagated
        sn y = x->c[d], z = x->p; prop(y); 
        setLink(x, y->c[d^1], d);
        setLink(y, x, d^1);
        setLink(z, y, dir(z, x));
        y->pp = x->pp; x->pp = NULL; // set y to be parent of x
    }
    sn splay(sn x) {
        propAnc(x);
        while (x && x->p) {
            sn y = x->p, z = y->p;
            int dy = dir(y, x), dz = dir(z, y);
            if (!z) rot(y, dy);
            else if (dy == dz) rot(z, dz), rot(y, dy);
            else rot(y, dy), rot(z, dz);
        }
        return x;
    }
    sn farthest(sn x, int d) { // get leftmost or rightmost node
        prop(x); return x->c[d]?farthest(x->c[d],d):splay(x);
    }
}

using namespace splayTree;