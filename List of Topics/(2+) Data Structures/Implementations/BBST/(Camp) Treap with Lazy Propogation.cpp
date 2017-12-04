// Easiest BBST
// 7 min
// https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/Treap.h

struct tnode {
    ll val, lazy;
    int pri, sz;
    tnode *c[2];
    
    tnode (ll v) {
        val = v, lazy = 0; 
        pri = rand()+(rand()<<15), sz = 1;
        c[0] = c[1] = NULL;
    }
    
    void propogate() {
        if (!lazy) return;
        val += lazy;
        F0R(i,2) if (c[i]) c[i]->lazy += lazy;
        lazy = 0;
    }
    
    void recalc() {
        sz = 1;
        F0R(i,2) if (c[i]) sz += c[i]->sz;
    }
    
    void inOrder() {
        cout << "NODE: " << val << " SIZE: " << sz << " PRIORITY: " << pri << "\n";
        if (c[0]) cout << "LEFT: " << c[0]->val << "\n";
        if (c[1]) cout << "RIGHT: " << c[1]->val << "\n";
        cout << "\n";
        if (c[0]) c[0]->inOrder();
        if (c[1]) c[1]->inOrder();
    }
};

pair<tnode*,tnode*> split(tnode* t, int v) { // >= v goes to the right
    if (!t) return {t,t};

    t->propogate();
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
    
tnode* merge(tnode* l, tnode* r) {
    if (!l) return r; 
    if (!r) return l;
    
    l->propogate(), r->propogate();
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
    return merge(merge(a.f, new tnode(v)),a.s);
}

tnode* del(tnode* x, int v) { // delete all values equal to v
    auto a = split(x,v);
    auto b = split(a.s,v+1);
    delete b.f;
    
    return merge(a.f,b.s);
}

tnode *root, *root1;

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    root = ins(root,1);
    root = ins(root,9);
    root = ins(root,3);
    root = ins(root,7);
    root = ins(root,4);
    root = del(root,4);
    
    root->inOrder();
    cout << "--------\n\n";
    root1 = ins(root1,10);
    root = merge(root,root1); 
    root->inOrder();
    cout << "--------\n\n";
    
    auto a = split(root,7);
    a.f->inOrder();
    cout << "--------\n\n";
    a.s->inOrder();
}
