// constant time, linearithmic space
// 5 min

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

struct RMQ {
    int stor[100000][17];
    void build(vi& x) {
        memset(stor,0,sizeof stor);
        F0R(i,x.size()) stor[i][0] = x[i];
        FOR(j,1,17) F0R(i,100000-(1<<(j-1))) 
            stor[i][j] = min(stor[i][j-1],stor[i+(1<<(j-1))][j-1]);
    }
    int query(int l, int r) {
        int x = 31-__builtin_clz(r-l+1);
        return min(stor[l][x],stor[r-(1<<x)+1][x]);
    }
};

RMQ R;

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	vi x; F0R(i,10) x.pb(rand()%100);
	F0R(i,10) cout << x[i] << " ";
	cout << "\n";
	R.build(x);
	F0R(i,10) {
	    int a = rand() % 10, b = rand() % 10; if (a > b) swap(a,b);
	    cout << a << " " << b << " " << R.query(a,b) << "\n";
	}
}

// read!
// ll vs. int!