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

int n,m,s, dp[501][1001];
vector<vi> edge;

void solve() {
    cin >> n >> m >> s;
    edge.clear();
    F0R(i,m) {
        int a,b,d,t; cin >> a >> b >> d >> t;
        edge.pb({a,b,d,t});
    }
    FOR(i,1,n+1) F0R(j,s+1) dp[i][j] = MOD;
    dp[1][s] = 0;
    F0Rd(j,s+1) for (auto a: edge) if (j >= a[2]) dp[a[1]][j-a[2]] = min(dp[a[1]][j-a[2]],dp[a[0]][j]+a[3]);
    int ans = MOD;
    F0Rd(j,s+1) ans = min(ans,dp[n][j]);
    if (ans == MOD) cout << "Wipeout!";
    else cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	int n; cin >> n;
	FOR(i,1,n+1) {
	    cout << "Episode #" << i << ": ";
	    solve();
	    cout << "\n";
	}
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
