/*
* Description: based off treap code
*/

struct snode {
    int val, sz;
    snode *p, *c[2];

    snode (int v) {
        val = v, sz = 1;
        c[0] = c[1] = p = NULL;
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

void setLink(snode* x, snode* y, int d) {
    if (x) x->c[d] = y, x->recalc();
    if (y) y->p = x;
}

int getDir(snode* x, snode* y) {
    if (!x) return -1;
    return x->c[0] == y ? 0 : 1;
}

void rot(snode* x, int d) {
    snode *y = x->c[d], *z = x->p;
    setLink(x, y->c[d^1], d);
    setLink(y, x, d^1);
    setLink(z, y, getDir(z, x));
}

snode* splay(snode* x) {
    while (x && x->p) {
        snode* y = x->p, *z = y->p;
        int dy = getDir(y, x), dz = getDir(z, y);
        if (!z) rot(y, dy);
        else if (dy == dz) rot(z, dz), rot(y, dy);
        else rot(y, dy), rot(z, dz);
    }
    return x;
}

pair<snode*,snode*> find(snode *cur, int v) { // x.f is result, x.s is lowest
    if (!cur) return {cur,cur};
    pair<snode*,snode*> x;
    if (cur->val >= v) {
        x = find(cur->c[0],v);
        if (!x.f) x.f = cur;
    } else x = find(cur->c[1],v); 
    if (!x.s) x.s = cur;
    return x;
}

snode* getmx(snode* x) {
    return x->c[1]?getmx(x->c[1]):x;
}

pair<snode*,snode*> split(snode* x, int v) {
    if (!x) return {x,x};
    auto y = find(x,v); y.s = splay(y.s);
    if (!y.f) return {y.s,NULL};
    
    y.f = splay(y.f); 
    auto z = y.f->c[0]; setLink(y.f,NULL,0), setLink(NULL,z,0);
    return {z,y.f};
}

// split by order ...

snode* merge(snode* x, snode* y) {
    if (!x) return y;
    x = splay(getmx(x));
    setLink(x,y,1);
    return x;
}

snode* ins(snode* x, int v) { // insert value v
    auto a = split(x,v);
    return merge(merge(a.f, new snode(v)),a.s);
}

snode* del(snode* x, int v) { // delete all values equal to v
    auto a = split(x,v), b = split(a.s,v+1);
    return merge(a.f,b.s);
}

snode* root;

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