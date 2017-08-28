// 1D range update, range query

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
const ll INF = 1e18;

template<int SZ> struct LazySegTree {
    ll sum[2*SZ], lazy[2*SZ];
    
    LazySegTree() {
        memset (sum,0,sizeof sum);
        memset (lazy,0,sizeof lazy);
    }
    
    void push(int ind, int L, int R) {
        sum[ind] += (R-L+1)*lazy[ind];
        if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
        lazy[ind] = 0;
    }
    
    void pull(int ind) {
        sum[ind] = sum[2*ind]+sum[2*ind+1];
    }
    
    void build() {
        for (int i = SZ-1; i > 0; --i) pull(i);
    }
    
    ll qsum(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
        push(ind,L,R);
        if (lo > R || L > hi) return 0;
        if (lo <= L && R <= hi) return sum[ind];
        
        int M = (L+R)/2;
        return qsum(lo,hi,2*ind,L,M)+qsum(lo,hi,2*ind+1,M+1,R);
    }
    
    void upd(int lo, int hi, int inc, int ind = 1, int L = 0, int R = SZ-1) {
        push(ind,L,R);
        if (hi < L || R < lo) return;
        if (lo <= L && R <= hi) {
            lazy[ind] = inc;
            push(ind,L,R);
            return;
        }
        
        int M = (L+R)/2;
        upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
        pull(ind);
    }
};

template<int SZ> struct BIT {
    ll bit[2][SZ+1];
    
    BIT() { memset(bit,0,sizeof bit); }
    
    void u(int ind, int hi, int val) {
        for(;hi <= SZ; hi += (hi&-hi)) bit[ind][hi] += val;
    }
    
    void upd(int hi, int val) {
        u(1,1,val), u(1,hi+1,-val);
        u(0,hi+1,hi*val);
    }
    void upd(int lo, int hi, int val) { upd(lo-1,-val), upd(hi,val); }
    
    ll qsum(int x) {
        ll c1 = 0, c0 = 0;
        for (int x1 = x; x1 > 0; x1 -= (x1&-x1))
            c1 += bit[1][x1], c0 += bit[0][x1];
        return c1*x+c0;
    }
    ll qsum(int x, int y) { return qsum(y)-qsum(x-1); }
};

int main() {
    LazySegTree<1<<17> seg;
    seg.upd(2,5,7);
    cout << seg.qsum(1,2) << " " << seg.qsum(4,6) << "\n"; // 7 14
    
    BIT<1<<17> bit;
    bit.upd(2,5,7);
    cout << bit.qsum(1,2) << " " << bit.qsum(4,6) << "\n";
}
