// http://blog.ruofeidu.com/treap-in-45-lines-of-c/
// https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/Treap.h

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
    int val, pri, sz = 1;
    tnode *c[2];
    tnode (int val): val(val), pri(rand()/2), sz(1) {
        c[0] = c[1] = NULL;
    }
    void recalc ();
};

int cnt(tnode* n) { return n ? n->sz : 0; }
void tnode::recalc() { sz = cnt(c[0]) + cnt(c[1]) + 1; }

void rot (tnode *&p, int d) { // takes care of both left / right rotations
    tnode *q = p->c[d];
    p->c[d] = q->c[d^1];
    q->c[d^1] = p;
    p->recalc(), q->recalc();
    p = q;
}

void ins(tnode *&p, int x, int tmp = 0){
    if (!p) {
        p = new tnode(x);
        if (tmp) p->pri = INT_MAX;
    } else {
        if (x == p->val) {
            p->pri = INT_MAX;
            return;
        }
        int t = (x < p->val) ? 0 : 1;
        ins(p->c[t], x,tmp);
        if (p->c[t]->pri > p->pri) rot(p,t);
    }
    p->recalc();
}

void del(tnode *&p){
    F0R(t,2) if (!p->c[t]) {
        tnode* tmp = p->c[t^1];
        delete p; p = tmp;
        return;
    }
    int t = (p->c[0]->pri > p->c[1]->pri) ? 0 : 1;
    rot(p,t); del(p->c[t^1]);
    p->recalc();
}

void del(tnode *&p, int x){
    if (!p) return;
    if (p->val == x) del(p);
    else {
        int t = (x < p->val) ? 0 : 1;
        del(p->c[t],x);
    }
    if (p) p->recalc();
}

bool find(tnode *&p, int x) {
    if (!p) return 0;
    if (p->val == x) return 1;
    int t = p->val < x ? 0 : 1;
    return find(p->c[t],x);
}

int order_of_key(tnode *&p, int x){ // how many less than x
    if (!p) return 0;
    if (x <= p->val) return order_of_key(p->c[0],x);
    return order_of_key(p->c[1],x)+1+cnt(p->c[0]);
}

int find_by_order(tnode *&p, int x) {
    if (!p) return MOD;
    if (cnt(p->c[0]) == x) return p->val;
    if (cnt(p->c[0]) < x) return find_by_order(p->c[1],x-cnt(p->c[0])-1);
    return find_by_order(p->c[0],x);
}

tnode *root, *root1;

void inOrder(tnode *&cur) {
    if (!cur) return;
    cout << "NODE " << cur->val << " PRIORITY: " << cur->pri << " SIZE " << cur->sz << "\n";
    if (cur->c[0]) cout << "LEFT: " << cur->c[0]->val << "\n";
    if (cur->c[1]) cout << "RIGHT: " << cur->c[1]->val << "\n";
    cout << "\n";
    inOrder(cur->c[0]);
    inOrder(cur->c[1]);
}

pair<tnode*,tnode*> split(tnode* cur, int k) { // one with all values < k, other with all values > k
    ins(cur,k,1);
    pair<tnode*,tnode*> ans = {cur->c[0],cur->c[1]};
    delete cur;
    return ans;
}

tnode* merge(tnode* a, tnode* b) {
    tnode* x = new tnode(0); x->pri = INT_MAX;
    x->c[0] = a, x->c[1] = b;
    del(x); return x;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    ins(root,1);
    ins(root,9);
    ins(root,3);
    ins(root,7);
    ins(root,4);
    del(root,4);
    
    inOrder(root);
    cout << "--------\n\n";
    ins(root1,10);
    root = merge(root,root1); // fix this??
    inOrder(root);
    cout << "--------\n\n";
    
    auto a = split(root,7);
    inOrder(a.f);
    cout << "--------\n\n";
    inOrder(a.s);
}

// read!
// ll vs. int!
