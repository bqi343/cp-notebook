/**
* Sources: Dhruv Rohatgi,
*           https://sites.google.com/site/kc97ble
*           /container/splay-tree/splaytree-cpp-3
* Usage: SPOJ DYNACON1
*/

struct snode {
    int id, sz;
    bool flip;
    snode *p, *pp, *c[2];
    
    snode (int id){ sz = 1, flip = 0; c[0] = c[1] = p = pp = NULL; }
    snode (): snode(0) {}
    
    void inOrder(bool f = 0) {
        if (c[0]) c[0]->inOrder();
        cout << id << " ";
        if (c[1]) c[1]->inOrder();
        if (f) cout << "\n------------\n";
    }
    
    void recalc() {
        sz = 1+(c[0]?c[0]->sz:0)+(c[1]?c[1]->sz:0);
    }
    
    void prop() {
        if (!flip) return; 
        swap(c[0],c[1]);
        if (c[0]) c[0]->flip ^= 1;
        if (c[1]) c[1]->flip ^= 1;
        flip = 0;
    }
};

snode* S[MX];

int getsz(snode* x) { return x?x->sz:0; }

int getDir(snode* x, snode* y) { return x ? x->c[0] != y : -1; }

///////////// SPLAY TREE OPERATIONS

void setLink(snode* x, snode* y, int d) {
    if (x) x->c[d] = y, x->recalc();
    if (y) y->p = x;
}

void disLink(snode* x, snode* y, int d) {
    if (x) x->c[d] = NULL, x->recalc();
    if (y) y->p = NULL;
}

void rot(snode* x, int d) {
    snode *y = x->c[d], *z = x->p;
    setLink(x, y->c[d^1], d);
    setLink(y, x, d^1);
    setLink(z, y, getDir(z, x));
    y->pp = x->pp; x->pp = NULL;
}

void pushDown(snode* x) {
    if (!x) return;
    if (x->p) pushDown(x->p);
    x->prop();
}

void splay(snode* x) {
    pushDown(x);
    while (x && x->p) {
        snode* y = x->p, *z = y->p;
        int dy = getDir(y, x), dz = getDir(z, y);
        if (!z) rot(y, dy);
        else if (dy == dz) rot(z, dz), rot(y, dy);
        else rot(y, dy), rot(z, dz);
    }
}

///////////// LINK CUT TREE OPERATIONS

void con(snode* x, int d) { 
    setLink(x->pp,x,d); 
    x->pp = NULL; 
}

void dis(snode* x, int d) { 
    snode* y = x->c[d];
    disLink(x,y,d); 
    if (y) y->pp = x;
}

void access(snode* x) { // v is brought to the root of auxiliary tree
    splay(x); dis(x,1);
    while (x->pp) {
        splay(x->pp);
        dis(x->pp,1), con(x,1);
        splay(x);
    }
}

void link(snode* v, snode* w) { // v, which is root of another tree, is now child of w
    access(v), access(w);
    w->pp = v; con(w,0);
}

void cut(snode* x) { // cut link between v and par[v]
    access(x); snode* y = x->c[0];
    dis(x,0); y->pp = NULL;
}

///////////// QUERIES

snode* find_root(snode* v) {
    access(v); while (v->c[0]) v = v->c[0];
    access(v); return v;
}

int find_depth(snode* v) { access(v); return getsz(v->c[0]); }

snode* anc(snode* v, int num) {
    if (find_depth(v) < num) return NULL;
    access(v); v = v->c[0];
    
    while (1) {
        int s = getsz(v->c[1]);
        if (s >= num) v = v->c[1];
        else if (s+1 == num) return v;
        else num -= (s+1), v = v->c[0];
    }
}

void make_root(snode* v) { access(v); v->flip = 1; }