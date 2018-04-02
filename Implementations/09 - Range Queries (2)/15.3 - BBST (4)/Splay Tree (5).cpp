/*
* Description: Based off treap code
* Source: https://sites.google.com/site/kc97ble
*           /container/splay-tree/splaytree-cpp-3
* Verification: http://www.spoj.com/problems/ORDERSET/
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

snode* unLink(snode* x, int d) {
    snode* y = x->c[d];
    x->c[d] = NULL; x->recalc();
    if (y) y->p = NULL;
    return y;
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

snode* find(snode *cur, int v) { 
    if (!cur) return cur;
    snode* x;
    if (cur->val >= v) x = find(cur->c[0],v);
    else x = find(cur->c[1],v); 
    return x?x:cur;
}

snode* getmx(snode* x) {
    return x->c[1]?getmx(x->c[1]):x;
}

pair<snode*,snode*> split(snode* x, int v) {
    if (!x) return {x,x};
    snode* y = find(x,v); y = splay(y);
    if (y->val >= v) return {unLink(y,0),y};
    else return {y,unLink(y,1)};
}

snode* find_by_order(snode* x, int v) {
    int tmp = x->c[0]?x->c[0]->sz:0;
    if (v < tmp) return find_by_order(x->c[0],v);
    else if (v == tmp) return x;
    else return find_by_order(x->c[1],v-tmp-1);
}

pair<snode*,snode*> split_by_order(snode* x, int v) { // left subtree has v elements
    if (!x) return {x,x};
    if (v == x->sz) return {x,NULL};
    snode* y = find_by_order(x,v); y = splay(y);
    return {unLink(y,0),y};
}

snode* merge(snode* x, snode* y) {
    if (!x) return y;
    x = splay(getmx(x));
    setLink(x,y,1);
    return x;
}

// same as treap

snode* ins(snode* x, int v) { // insert value v
    auto a = split(x,v);
    auto b = split(a.s,v+1);
    return merge(a.f,merge(new snode(v),b.s));
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