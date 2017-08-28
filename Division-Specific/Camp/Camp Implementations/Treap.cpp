// http://blog.ruofeidu.com/treap-in-45-lines-of-c/
// https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/Treap.h

#include <bits/extc++.h>

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

struct node {
    int val, pri, sz = 1;
    node *c[2];
    node (int val): val(val), pri(rand()), sz(1) {}
    void recalc ();
};

int cnt(node* n) { return n ? n->sz : 0; }
void node::recalc() { sz = cnt(c[0]) + cnt(c[1]) + 1; }

void rot (node *&p, int d) { // takes care of both left / right rotations
    node *q = p->c[d]; 
    p->c[d] = q->c[d^1]; 
    q->c[d^1] = p; 
    p->recalc(), q->recalc();
    p = q;
}
        
void ins(node *&p, int x){
    if (!p) p = new node(x);
    else {
        if (x == p->val) return;
        int t = (x < p->val) ? 0 : 1;
        ins(p->c[t], x); 
        if (p->c[t]->pri > p->pri) rot(p,t);
    }
    p->recalc();
}

void del(node *&p){ 
    F0R(t,2) if (!p->c[t]) {
        node* tmp = p->c[t^1];
        delete p; p = tmp;
        return;
    }
    int t = (p->c[0]->pri > p->c[1]->pri) ? 0 : 1;
    rot(p,t); del(p->c[t^1]);
    p->recalc(); 
}

void del(node *&p, int x){
    if (!p) return;
    if (p->val == x) del(p); 
    else {
        int t = (x < p->val) ? 0 : 1;
        del(p->c[t],x); 
    }
    if (p) p->recalc();
}     

bool find(node *&p, int x) {
    if (!p) return 0;
    if (p->val == x) return 1;
    int t = p->val < x ? 0 : 1;
    return find(p->c[t],x);
}
        
int order_of_key(node *&p, int x){ // how many less than x
    if (!p) return 0; 
    if (x <= p->val) return order_of_key(p->c[0],x);
    return order_of_key(p->c[1],x)+1+cnt(p->c[0]);
}
        
int find_by_order(node *&p, int x) {
    if (!p) return MOD;
    if (cnt(p->c[0]) == x) return p->val; 
    if (cnt(p->c[0]) < x) return find_by_order(p->c[1],x-cnt(p->c[0])-1);
    return find_by_order(p->c[0],x);
}

node* root;

void inOrder(node*& cur) {
    if (!cur) return;
    cout << "NODE " << cur->val << " PRIORITY: " << cur->pri << " SIZE " << cur->sz << "\n";
    if (cur->c[0]) cout << "LEFT: " << cur->c[0]->val << "\n";
    if (cur->c[1]) cout << "RIGHT: " << cur->c[1]->val << "\n";
    cout << "\n";
    inOrder(cur->c[0]);
    inOrder(cur->c[1]);
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
}

// read!
// ll vs. int!