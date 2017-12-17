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
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;

struct Node { // without lazy updates
    int val = 0;
    Node* c[2];
    
    Node* copy() {
        Node* x = new Node(); *x = *this;
        return x;
    }
    
    int query(int low, int high, int L, int R) {  
        if (low <= L && R <= high) return val;
        if (R < low || high < L) return MOD;
        int M = (L+R)/2;
        return min(c[0]->query(low,high,L,M),c[1]->query(low,high,M+1,R));
    }
    
    Node* upd(int ind, int v, int L, int R) {
        if (R < ind || ind < L) return this;
        Node* x = copy();
        
        if (ind <= L && R <= ind) {
            x->val += v;
            return x;
        }
        
        int M = (L+R)/2;
        x->c[0] = x->c[0]->upd(ind,v,L,M);
        x->c[1] = x->c[1]->upd(ind,v,M+1,R);
        x->val = min(x->c[0]->val,x->c[1]->val);
        
        return x;
    }
    
    void build(vi& arr, int L, int R) {
        if (L == R) {
            if (L < (int)arr.size()) val = arr[L];
            else val = 0;
            return;
        }
        int M = (L+R)/2;
        c[0] = new Node();
        c[0]->build(arr,L,M);
        c[1] = new Node();
        c[1]->build(arr,M+1,R);
        val = min(c[0]->val,c[1]->val);
    }
};

struct node { // with lazy updates
    int val = 0, lazy = 0;
    node* c[2];
    
    node* copy() {
        node* x = new node(); *x = *this;
        return x;
    }
    
    void push() {
        if (!lazy) return;
        F0R(i,2) if (c[i]) {
            c[i] = new node(*c[i]);
            c[i]->lazy += lazy;
        }
        lazy = 0;
    }
    
    int query(int low, int high, int L, int R) {  
        if (low <= L && R <= high) return val;
        if (R < low || high < L) return MOD;
        int M = (L+R)/2;
        int t = min(c[0]->query(low,high,L,M),c[1]->query(low,high,M+1,R));
        return lazy+t;
    }
    
    node* upd(int low, int high, int v, int L, int R) {
        if (R < low || high < L) return this;
<<<<<<< HEAD
=======
        node* x = copy();
>>>>>>> f061d418025a4f9d4d29291a50c39c4bb67efc3e
        if (low <= L && R <= high) {
            x->lazy += v, x->val += v;
            return x;
        }
        push();
<<<<<<< HEAD
        node* x = copy();
=======
>>>>>>> f061d418025a4f9d4d29291a50c39c4bb67efc3e
        
        int M = (L+R)/2;
        x->c[0] = x->c[0]->upd(low,high,v,L,M);
        x->c[1] = x->c[1]->upd(low,high,v,M+1,R);
        x->val = min(x->c[0]->val,x->c[1]->val);
        
        return x;
    }
    
    void build(vi& arr, int L, int R) {
        if (L == R) {
            if (L < sz(arr)) val = arr[L];
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
        loc[nex] = loc[nex-1]->upd(low,high,val,0,SZ-1);
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
