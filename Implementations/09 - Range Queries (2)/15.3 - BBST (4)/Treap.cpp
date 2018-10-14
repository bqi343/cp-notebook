/*
* Source: https://cp-algorithms.com/data_structures/treap.html + others
* Description: Easiest BBST
* Verification: http://www.spoj.com/problems/ORDERSET/
*/

namespace treap {
    typedef struct tnode* pt;
    
    struct tnode {
        int pri, val; pt c[2]; // essential
        int sz; ll sum; // for range queries
    
        tnode (int _val) {
            pri = rand()+(rand()<<15); val = _val; c[0] = c[1] = NULL;
            sz = 1; sum = val;
        }
    };
    
    int getsz(pt x) { return x?x->sz:0; }
    ll getsum(pt x) { return x?x->sum:0; }
    
    void trav(pt x, vi& v) {
        if (!x) return;
        trav(x->c[0],v); v.pb(x->val); trav(x->c[1],v);
    }
    
    pt recalc(pt x) {
        x->sz = 1+getsz(x->c[0])+getsz(x->c[1]);
        x->sum = x->val+getsum(x->c[0])+getsum(x->c[1]);
        return x;
    }
    
    pair<pt,pt> split(pt t, int v) { // >= v goes to the right
        if (!t) return {t,t};
        if (t->val >= v) {
            auto p = split(t->c[0], v); t->c[0] = p.s;
            return {p.f, recalc(t)};
        } else {
            auto p = split(t->c[1], v); t->c[1] = p.f;
            return {recalc(t), p.s};
        }
    }
    
    pair<pt,pt> splitsz(pt t, int sz) {
        if (!t) return {t,t};
        if (getsz(t->c[0]) >= sz) {
            auto p = splitsz(t->c[0], sz); t->c[0] = p.s;
            return {p.f, recalc(t)};
        } else {
            auto p = splitsz(t->c[1], sz-getsz(t->c[0])-1); t->c[1] = p.f;
            return {recalc(t), p.s};
        }
    }
        
    pt merge(pt l, pt r) {
        if (!l || !r) return l ? l : r;
        pt t;
        if (l->pri > r->pri) l->c[1] = merge(l->c[1],r), t = l;
        else r->c[0] = merge(l,r->c[0]), t = r;
        return recalc(t);
    }
    
    pt ins(pt x, int v) { // insert v
        auto a = split(x,v), b = split(a.s,v+1);
        return merge(a.f,merge(new tnode(v),b.s));
    }
    
    pt del(pt x, int v) { // delete v
        auto a = split(x,v), b = split(a.s,v+1);
        return merge(a.f,b.s);
    }
}

using namespace treap;