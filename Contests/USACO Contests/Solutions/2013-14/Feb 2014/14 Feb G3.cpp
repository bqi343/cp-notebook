#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

struct tnode {
    pi val; // y, x
    int pri, lazy;
    tnode *c[2];
    tnode (pi v) {
        c[0] = c[1] = NULL;
        pri = rand(); // note that this is < (1<<15) on windows!
        val = v; lazy = 0;
    }
    
    void propogate() {
        val.f += lazy;
        if (c[0]) c[0]->lazy += lazy;
        if (c[1]) c[1]->lazy += lazy;
        lazy = 0;
    }
};

pair<tnode*,tnode*> split(tnode* t, int y) { // >= y goes to the right
    if (!t) return {t,t};

    t->propogate();
    if (y <= t->val.f) {
        pair<tnode*,tnode*> p = split(t->c[0], y);
        t->c[0] = p.s;
        return {p.f, t};
    } else {
        pair<tnode*,tnode*> p = split(t->c[1], y);
        t->c[1] = p.f; 
        return {t, p.s};
    }
} // OK
    
tnode* merge(tnode* l, tnode* r) {
    if (!l) return r; 
    if (!r) return l;
    l->propogate(), r->propogate();
    if (l->pri > r->pri) {
        l->c[1] = merge(l->c[1],r);
        return l;
    } else {
        r->c[0] = merge(l,r->c[0]);
        return r;
    }
} // OK

int get(tnode* x) {
    if (!x) return -MOD;
    x->propogate();
    if (x->c[0]) return get(x->c[0]);
    return x->val.f-x->val.s;
}

tnode* rem(tnode* x) {
    x->propogate();
    if (x->c[0]) {
        x->c[0] = rem(x->c[0]);
        return x;
    } else {
        tnode* x1 = x;
        x = x->c[1];
        delete x1;
        return x;
    }
}

tnode* ins(tnode* x, pi v) {
    auto a = split(x,v.f);
    tnode* z = new tnode(v);
    while (get(a.s) >= v.f-v.s) a.s = rem(a.s);
    return merge(merge(a.f,z),a.s);
}

tnode *root;
int N, S[200001], T[200001], ans;

pi getlst(tnode* x) {
    x->propogate();
    if (x->c[1]) return getlst(x->c[1]);
    return x->val;
}

int process(int s, int t) {
    auto a = split(root,s);
    if (a.s) a.s->lazy ++;
    pi tmp = getlst(a.f);
    tmp.s += s+t-tmp.f;
    tmp.f = s;
    root = merge(a.f,a.s);
    root = ins(root,tmp);
    return tmp.s;
}

int main() {
    freopen("boarding.in","r",stdin);
    freopen("boarding.out","w",stdout);
    ios_base::sync_with_stdio(0);cin.tie(0);
    root = ins(root,{0,0});
    cin >> N;
    FOR(i,1,N+1) {
        cin >> S[i] >> T[i];
        S[i] += N-i;
    }
    FORd(i,1,N+1) ans = max(ans,process(S[i],T[i]));
    cout << ans;
}

// read!
// ll vs. int!
