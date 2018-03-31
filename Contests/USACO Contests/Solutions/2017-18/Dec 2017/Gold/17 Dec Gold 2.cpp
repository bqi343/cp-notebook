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
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;

int N,K, col[100001];
ll dp[100001][4];
vi adj[100001];

void dfs(int pre, int cur) {
    if (col[cur] == 0) dp[cur][1] = dp[cur][2] = dp[cur][3] = 1;
    else dp[cur][col[cur]] = 1;
    
    for (int i: adj[cur]) if (i != pre) {
        dfs(cur,i);
        dp[cur][1] *= dp[i][2]+dp[i][3];
        dp[cur][2] *= dp[i][1]+dp[i][3];
        dp[cur][3] *= dp[i][2]+dp[i][1];
        FOR(j,1,4) dp[cur][j] %= MOD;
    }
}

int main() {
    freopen("barnpainting.in","r",stdin);
    freopen("barnpainting.out","w",stdout);
	cin >> N >> K;
	F0R(i,N-1) {
	    int x,y; cin >> x >> y;
	    adj[x].pb(y), adj[y].pb(x);
	}
	F0R(i,K) {
	    int b,c; cin >> b >> c;
	    col[b] = c;
	}
	dfs(0,1);
	ll ans = 0; FOR(i,1,4) ans += dp[1][i];
	cout << ans%MOD;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
