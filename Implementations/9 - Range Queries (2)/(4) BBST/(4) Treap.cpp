/*
* Sources: various
* Description: Easiest BBST
* Verification: http://www.spoj.com/problems/ORDERSET/
*/

struct tnode {
    int val, pri, sz;
    tnode *c[2];

    tnode (int v) {
        val = v, sz = 1, pri = rand()+(rand()<<15);
        c[0] = c[1] = NULL;
    }
    
    void inOrder(bool f = 0) {
        if (c[0]) c[0]->inOrder();
        cout << val << " ";
        if (c[1]) c[1]->inOrder();
        if (f) cout << "\n------------\n";
    }
    
    void recalc() {
        sz = 1+(c[0]?c[0]->sz:0)+(c[1]?c[1]->sz:0);
    }
};

pair<tnode*,tnode*> split(tnode* t, int v) { // >= v goes to the right
    if (!t) return {t,t};
    
    if (v <= t->val) {
        auto p = split(t->c[0], v); 
        t->c[0] = p.s; t->recalc();
        return {p.f, t};
    } else {
        auto p = split(t->c[1], v); 
        t->c[1] = p.f; t->recalc();
        return {t, p.s};
    }
}
    
pair<tnode*,tnode*> split_by_order(tnode* t, int v) {
    if (!t) return {t,t};
    int tmp = t->c[0]?t->c[0]->sz:0;
    if (v <= tmp) {
        auto p = split_by_order(t->c[0], v);
        t->c[0] = p.s; t->recalc();
        return {p.f, t};
    } else {
        auto p = split_by_order(t->c[1], v-tmp-1); 
        t->c[1] = p.f; t->recalc();
        return {t, p.s};
    }
}

tnode* merge(tnode* l, tnode* r) {
    if (!l) return r; 
    if (!r) return l;
    
    if (l->pri > r->pri) {
        l->c[1] = merge(l->c[1],r);
        l->recalc();
        return l;
    } else {
        r->c[0] = merge(l,r->c[0]);
        r->recalc();
        return r;
    }
}

tnode* ins(tnode* x, int v) { // insert value v
    auto a = split(x,v);
    auto b = split(a.s,v+1);
    return merge(a.f,merge(new tnode(v),b.s));
}

tnode* del(tnode* x, int v) { // delete all values equal to v
    auto a = split(x,v), b = split(a.s,v+1);
    return merge(a.f,b.s);
}

tnode *root;

int order_of_key(int x) {
    auto a = split(root,x);
    int t = a.f?a.f->sz:0;
    root = merge(a.f,a.s);
    return t;
}

int find_by_order(int x) {
    auto a = split_by_order(root,x);
    auto b = split_by_order(a.f,x-1);
    int t = b.s->val;
    root = merge(merge(b.f,b.s),a.s);
    return t;
}