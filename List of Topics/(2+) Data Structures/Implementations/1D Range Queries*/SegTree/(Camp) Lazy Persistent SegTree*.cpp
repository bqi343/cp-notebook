// Persistent segment tree with lazy updates!

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

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

struct node {
    int val = 0, lazy = 0;
    node* c[2];
    
    void push() {
        if (!lazy) return;
        val += lazy;
        
        if (c[0]) {
            node* c0 = new node();
            *c0 = *c[0]; c0->lazy += lazy;
            c[0] = c0;
        }
        
        if (c[1]) { 
            node* c1 = new node();
            *c1 = *c[1]; c1->lazy += lazy;
            c[1] = c1;
        }
        
        lazy = 0;
    }
    
    int query(int low, int high, int L, int R) {  // queries minimum
        push();
        if (low <= L && R <= high) return val;
        if (R < low || high < L) return MOD;
        int M = (L+R)/2;
        return min(c[0]->query(low,high,L,M),c[1]->query(low,high,M+1,R));
    }
    
    void upd(node* ne, int low, int high, int val, int L, int R) {
        push();
        *ne = *this;
        if (low <= L && R <= high) {
            ne->lazy = val;
            ne->push();
            return;
        }
        if (R < low || high < L) return;
        
        int M = (L+R)/2;
        ne->c[0] = new node(), ne->c[1] = new node();
        c[0]->upd(ne->c[0],low,high,val,L,M);
        c[1]->upd(ne->c[1],low,high,val,M+1,R);
        ne->val = min(ne->c[0]->val,ne->c[1]->val);
    }
    
    void build(vi& arr, int L, int R) {
        if (L == R) {
            if (L < arr.size()) val = arr[L];
            else val = 0;
            return;
        }
        int M = (L+R)/2;
        c[0] = new node();
        c[0]->build(arr,L,M);
        c[1] = new node();
        c[1]->build(arr,M+1,R);
        val = min(c[0]->val,c[1]->val);
    }
};

template<int SZ> struct pers {
    node* loc[SZ+1]; // stores location of root after ith update
    int nex = 1;
    
    pers() { loc[0] = new node(); }
    
    void upd(int low, int high, int val) {
        loc[nex] = new node();
        loc[nex-1]->upd(loc[nex],low,high,val,0,SZ-1);
        nex++;
    }
    void build(vi& arr) { 
        loc[0]->build(arr,0,SZ-1);
    }
    int query(int ti, int low, int high) { 
        return loc[ti]->query(low,high,0,SZ-1);
    }
};

pers<8> p;

int main() {
    vi arr = {1,7,2,3,5,9,4,6};
    p.build(arr);
    
    p.upd(1,2,2); // 1 9 4 3 5 9 4 6
    F0R(i,8) {
        FOR(j,i,8) cout << p.query(1,i,j) << " ";
        cout << "\n";
    }
    cout << "\n";
    
    p.upd(4,7,5); // 1 9 4 3 10 14 9 11
    F0R(i,8) {
        FOR(j,i,8) cout << p.query(2,i,j) << " ";
        cout << "\n";
    }
    cout << "\n";
    
    F0R(i,8) {
        FOR(j,i,8) cout << p.query(1,i,j) << " ";
        cout << "\n";
    }
    cout << "\n";
}