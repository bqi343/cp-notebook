// Easiest BBST
// 7 min
// https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/Treap.h

struct tnode {
    int val, pri;
    tnode *c[2];
    tnode (int v) {
        c[0] = c[1] = NULL;
        pri = rand(); // note that this is < (1<<15) on windows!
        val = v;
    }
    
    void inOrder() {
        cout << "NODE " << val << " PRIORITY: " << pri << "\n";
        if (c[0]) cout << "LEFT: " << c[0]->val << "\n";
        if (c[1]) cout << "RIGHT: " << c[1]->val << "\n";
        cout << "\n";
        if (c[0]) c[0]->inOrder();
        if (c[1]) c[1]->inOrder();
    }
};

pair<tnode*,tnode*> split(tnode* t, int v) { // >= v goes to the right
    if (!t) return {t,t};

    if (v <= t->val) {
        pair<tnode*,tnode*> p = split(t->c[0], v);
        t->c[0] = p.s;
        return {p.f, t};
    } else {
        pair<tnode*,tnode*> p = split(t->c[1], v);
        t->c[1] = p.f; 
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

tnode* ins(tnode* x, int v) {
    auto a = split(x,v);
    auto b = split(a.s,v+1);
    delete b.f;
    
    tnode* z = new tnode(v);
    return merge(merge(a.f,z),b.s);
}

tnode* del(tnode* x, int v) {
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

// read!
// ll vs. int!
