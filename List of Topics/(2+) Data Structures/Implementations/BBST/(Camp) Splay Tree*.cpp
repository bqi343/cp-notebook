//http://codeforces.com/blog/entry/18462
//https://sites.google.com/site/kc97ble/container/splay-tree/splaytree-cpp-3

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

struct node{
    int val, sz;
    node *p, *c[2];
    node (int v) {
        val = v, sz = 1;
    }
    void recalc() {
        sz = 1;
        if (c[0]) sz += c[0]->sz;
        if (c[1]) sz += c[1]->sz;
    }
};

node *root;

void setLink(node *x, node *y, int d) {
    if (x) {
        x->c[d] = y;
        x->recalc();
    }
    if (y) y->p = x;
}

int getDir(node *x, node *y) {
    if (!x) return -1;
    return x->c[0] == y ? 0 : 1;
}

void rot(node *x, int d) {
    node *y = x->c[d], *z = x->p;
    setLink(x, y->c[d^1], d);
    setLink(y, x, d^1);
    setLink(z, y, getDir(z, x));
    x->recalc(), y->recalc();
}

void splay(node *x) {
    while (x->p) {
        node *y = x->p, *z = y->p;
        int dy = getDir(y, x), dz = getDir(z, y);
        if (!z) rot(y, dy);
        else if (dy == dz) rot(z, dz), rot(y, dy);
        else rot(y, dy), rot(z, dz);
    }
    root = x;
}

node* ins(node* cur, int v) {
    if (!cur) return cur = new node(v);
    if (cur->val == v) return cur;
    int t = v < cur->val ? 0 : 1;
    
    if (!cur->c[t]) {
        setLink(cur,new node(v),t);
        return cur->c[t];
    } else {
        node* x = ins(cur->c[t],v); 
        cur->recalc();
        return x;
    }
}

void ins(int val) {
    splay(ins(root,val));
}

bool find(node *cur, int v) {
    if (!cur) return 0;
    if (cur->val == v) {
        splay(cur);
        return 1;
    }
    return find(cur->c[v < cur->val ? 0 : 1],v);
}

bool del(int v) {
    if (!find(root,v)) return 0;
    node *N = root, *P = N->c[0];
    if(!P) {
        root = N->c[1]; root->p = NULL, delete N;
        return 1;
    }
    
    while(P->c[1]) P = P->c[1];
    setLink(P,N->c[1],1);
    root = N->c[0], root->p = NULL, delete N;
    
    while (P) {
        P->recalc();
        P = P->p;
    }
    return 1;
}

void inOrder(node* cur) {
    if (!cur) return;
    cout << "NODE " << cur->val << ": SIZE " << cur->sz << "\n";
    if (cur->c[0]) cout << "LEFT: " << cur->c[0]->val << "\n";
    if (cur->c[1]) cout << "RIGHT: " << cur->c[1]->val << "\n";
    cout << "\n";
    inOrder(cur->c[0]);
    inOrder(cur->c[1]);
}

int main() {
    for (int i = 0; i < 10; ++i) ins(rand() % 50);
    inOrder(root);
    cout << "--------\n\n";
    del(21);
    inOrder(root);
}

// read!
// ll vs int!
