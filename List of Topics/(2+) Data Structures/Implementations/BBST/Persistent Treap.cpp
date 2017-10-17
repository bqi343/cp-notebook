// https://github.com/radoslav11/Coding-Library/blob/master/data_structures/persistent_treap.cpp

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

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

tnode* copy(tnode* o) {
    if (!o) return o;
    tnode* x = new tnode(0); *x = *o;
    return x;
}

pair<tnode*,tnode*> split(tnode* t, int v) { // >= x goes to the right
    if (!t) return {t,t};
    
    tnode* T = copy(t);
    if (v <= t->val) {
        pair<tnode*,tnode*> p = split(T->c[0], v);
        T->c[0] = p.s;
        return {p.f, T};
    } else {
        pair<tnode*,tnode*> p = split(T->c[1], v);
        T->c[1] = p.f; 
        return {T, p.s};
    }
}
    
tnode* merge(tnode* l, tnode* r) {
    if (!l) return r; 
    if (!r) return l;
    if (l->pri > r->pri) {
        tnode* L = copy(l);
        L->c[1] = merge(L->c[1],r);
        return L;
    } else {
        tnode* R = copy(r);
        R->c[0] = merge(l,R->c[0]);
        return R;
    }
}

tnode* ins(tnode* x, int v) {
    auto a = split(x,v);
    auto b = split(a.s,v+1);
    
    tnode* z = new tnode(v);
    return merge(merge(a.f,z),b.s);
}

tnode* del(tnode* x, int v) {
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
    
    root = ins(root,7);
    root = ins(root,4);
    root = del(root,9);
    
    root1->inOrder();
    cout << "----\n";
    root->inOrder();
}

// read!
// ll vs. int!
