// Easiest BBST
// https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/Treap.h
// lazy persistent order statistics tree!

struct tnode {
    ll val, lazy;
    int pri, sz;
    tnode *c[2];
    
    tnode* copy() {
        tnode* x = new tnode(0); *x = *this;
        return x;
    }

    tnode (ll v) {
        val = v, lazy = 0; 
        pri = rand()+(rand()<<15), sz = 1;
        c[0] = c[1] = NULL;
    }
    
    void propogate() {
        if (!lazy) return;
        val += lazy;
        F0R(i,2) if (c[i]) {
            c[i] = c[i]->copy();
            c[i]->lazy += lazy;
        }
        lazy = 0;
    }
    
    void recalc() {
        sz = 1;
        F0R(i,2) if (c[i]) sz += c[i]->sz;
    }
    
    void inOrder(bool f = 0) {
        propogate();
        if (c[0]) c[0]->inOrder();
        cout << val << " ";
        if (c[1]) c[1]->inOrder();
        if (f) cout << "\n------------\n";
    }
};

pair<tnode*,tnode*> split(tnode* t, int v) { // >= v goes to the right
    if (!t) return {t,t};

    t->propogate();
    tnode* T = t->copy();
    
    if (v <= T->val) {
        auto p = split(T->c[0], v);
        T->c[0] = p.s; T->recalc();
        return {p.f, T};
    } else {
        auto p = split(T->c[1], v);
        T->c[1] = p.f; T->recalc();
        return {T, p.s};
    }
}
    
tnode* merge(tnode* l, tnode* r) {
    if (!l) return r; 
    if (!r) return l;
    
    l->propogate(), r->propogate();
    if (l->pri > r->pri) {
        tnode* L = l->copy();
        L->c[1] = merge(L->c[1],r);
        L->recalc();
        return L;
    } else {
        tnode* R = r->copy();
        R->c[0] = merge(l,R->c[0]);
        R->recalc();
        return R;
    }
}

tnode* ins(tnode* x, int v) { // insert value v
    auto a = split(x,v);
    return merge(merge(a.f, new tnode(v)),a.s);
}

tnode* del(tnode* x, int v) { // delete all values equal to v
    auto a = split(x,v);
    auto b = split(a.s,v+1);
    return merge(a.f,b.s);
}

tnode *root, *root1;

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    
    root = ins(root,1);
    root = ins(root,9);
    root = ins(root,3);
    
    root1 = root;
    root1->inOrder(1);
    
    root = ins(root,7);
    root = ins(root,4);
    root = del(root,9);
    
    root->inOrder(1);
    root1->inOrder(1);
    cout << root->sz << " " << root1->sz << "\n";
}

/*
Output:

1 3 9 
------------
1 3 4 7 
------------
1 3 9 
------------
4 3

*/