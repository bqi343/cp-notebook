// 1D range update, range query
// 6 min

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

template<int SZ> struct BIT {
    ll bit[2][SZ+1]; // sums piecewise linear functions
    
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
    BIT<1<<17> bit;
    bit.upd(2,5,7);
    cout << bit.qsum(1,2) << " " << bit.qsum(4,6) << "\n"; // 7 14
}
