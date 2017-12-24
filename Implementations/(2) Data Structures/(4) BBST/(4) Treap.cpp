/*
* Sources: various
* Description: Easiest BBST
*/

struct tnode {
    int val, pri;
    tnode *c[2];

    tnode (int v) {
        val = v, pri = rand()+(rand()<<15);
        c[0] = c[1] = NULL;
    }
    
    void inOrder(bool f = 0) {
        if (c[0]) c[0]->inOrder();
        cout << val << " ";
        if (c[1]) c[1]->inOrder();
        if (f) cout << "\n------------\n";
    }
};

pair<tnode*,tnode*> split(tnode* t, int v) { // >= v goes to the right
    if (!t) return {t,t};
    
    if (v <= t->val) {
        auto p = split(t->c[0], v); t->c[0] = p.s; 
        return {p.f, t};
    } else {
        auto p = split(t->c[1], v); t->c[1] = p.f; 
        return {t, p.s};
    }
}
    
tnode* merge(tnode* l, tnode* r) {
    if (!l) return r; 
    if (!r) return l;
    
    if (l->pri > r->pri) {
        l->c[1] = merge(l->c[1],r);
        return l;
    } else {
        r->c[0] = merge(l,r->c[0]);
        return r;
    }
}

tnode* ins(tnode* x, int v) { // insert value v
    auto a = split(x,v);
    return merge(merge(a.f, new tnode(v)),a.s);
}

tnode* del(tnode* x, int v) { // delete all values equal to v
    auto a = split(x,v), b = split(a.s,v+1);
    return merge(a.f,b.s);
}

tnode *root;