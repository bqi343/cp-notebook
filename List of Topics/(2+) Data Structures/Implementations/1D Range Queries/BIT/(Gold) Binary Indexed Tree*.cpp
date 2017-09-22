// 1D point update, range query

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
    int bit[SZ+1];
    
    BIT() {
        memset(bit,0,sizeof bit);
    }
    
    void upd(int k, int val) {
        for( ;k <= SZ; k += (k&-k)) bit[k] += val;
    }
    
    int query(int k) {
        int temp = 0;
        for (;k > 0;k -= (k&-k)) temp += bit[k];
        return temp;
    }
    int query(int l, int r) { return query(r)-query(l-1); }
};

int main() {
    BIT<1<<17> b;
    b.upd(5,2);
    b.upd(4,1);
    cout << b.query(3,5) << "\n";
}