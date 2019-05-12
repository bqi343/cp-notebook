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

int n;

void solve() {
    double r,s; cin >> r >> s;
    int ans = 0;
    for (int i = 1;;++i) {
        double cur = s*(2*i-1)/2;
        if (cur > r) break;
        double tmp = (2*sqrt(r*r-cur*cur))/s;
        if (i == 1) ans += floor(tmp);
        else ans += 2*floor(tmp);
    }
    cout << int(ans*s*s) << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n;
    FOR(i,1,n+1) {
        cout << "Measure #" << i << ": ";
        solve();
    }
}

// read!
// ll vs. int!
