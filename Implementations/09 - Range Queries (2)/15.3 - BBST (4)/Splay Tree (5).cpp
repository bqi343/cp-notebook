/**
* Description: Treap alternative
* Sources: see LCT
*/

struct snode {
    int id, num = 1;
    bool flip = 0;
    snode *p, *pp, *c[2];

    snode (int _id) { 
        id = _id;
        c[0] = c[1] = p = pp = NULL; 
    }

    void inOrder(bool f = 0) {
        if (c[0]) c[0]->inOrder();
        cout << id << " ";
        if (c[1]) c[1]->inOrder();
        if (f) cout << "\n------------\n";
    }

    void recalc() {
        num = 1+(c[0]?c[0]->num:0)+(c[1]?c[1]->num:0);
    }
};

int getNum(snode* x) { return x?x->num:0; }
int getDir(snode* x, snode* y) { return x?(x->c[1] == y):-1; }

void prop(snode* x) {
    if (!x || !x->flip) return; 
    swap(x->c[0],x->c[1]);
    if (x->c[0]) x->c[0]->flip ^= 1;
    if (x->c[1]) x->c[1]->flip ^= 1;
    x->flip = 0;
}

void setLink(snode* x, snode* y, int d) { // x propagated
    if (x) x->c[d] = y, x->recalc();
    if (y) y->p = x;
}

void pushDown(snode* x) {
    if (!x) return;
    if (x->p) pushDown(x->p);
    prop(x);
}

void rot(snode* x, int d) { // precondition: x & parents propagated
    snode *y = x->c[d], *z = x->p;
    prop(y);
    setLink(x, y->c[d^1], d);
    setLink(y, x, d^1);
    setLink(z, y, getDir(z, x));
    y->pp = x->pp; x->pp = NULL;
}

snode* splay(snode* x) {
    pushDown(x);
    while (x && x->p) {
        snode* y = x->p, *z = y->p;
        int dy = getDir(y, x), dz = getDir(z, y);
        if (!z) rot(y, dy);
        else if (dy == dz) rot(z, dz), rot(y, dy);
        else rot(y, dy), rot(z, dz);
    }
    return x;
}
