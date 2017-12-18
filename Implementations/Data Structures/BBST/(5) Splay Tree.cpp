/*
* Based off treap code.
*/

struct snode {
    int val;
    snode *p, *c[2];
    snode (int v) {
        val = v;
        c[0] = c[1] = p = NULL;
    }
    void inOrder(bool f = 0) {
        if (c[0]) c[0]->inOrder();
        cout << val << " ";
        if (c[1]) c[1]->inOrder();
        if (f) cout << "\n------------\n";
    }
};

void setLink(snode* x, snode* y, int d) {
    if (x) x->c[d] = y;
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
    if (!x) return x;
    while (x->p) {
        snode* y = x->p, *z = y->p;
        int dy = getDir(y, x), dz = getDir(z, y);
        if (!z) rot(y, dy);
        else if (dy == dz) rot(z, dz), rot(y, dy);
        else rot(y, dy), rot(z, dz);
    }
    return x;
}

snode* find(snode *cur, int v) { // first one >= v
    if (!cur) return NULL;
    snode* x;
    if (cur->val >= v) {
        x = find(cur->c[0],v);
        return x?x:cur;
    } 
    return find(cur->c[1],v);
}

snode* getmx(snode* x) {
    if (!x) return x;
    if (x->c[1]) return getmx(x->c[1]);
    return x;
}

pair<snode*,snode*> split(snode* x, int v) {
    if (!x) return {x,x};
    snode* y = find(x,v);
    if (!y) return {splay(getmx(x)),NULL};
    
    y = splay(y); 
    auto z = y->c[0]; setLink(y,NULL,0), setLink(NULL,z,0);
    return {z,y};
}

snode* merge(snode* x, snode* y) {
    if (!x) return y;
    if (!y) return x;
    
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
    
int main() {
    root = ins(root,1);
    root = ins(root,9);
    root = ins(root,3);
    
    root->inOrder(1);
    
    root = ins(root,7);
    root = ins(root,4);
    root = del(root,9);
    
    root->inOrder(1);
}
