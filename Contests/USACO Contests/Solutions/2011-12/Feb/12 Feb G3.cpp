/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
double PI = 4*atan(1);

int N,K;
int dp[100001][21], C[100001];
vi adj[100001];

void dfs1(int par, int node) {
    for (int i: adj[node]) if (i != par) {
        dfs1(node,i);
        F0R(j,K) dp[node][j+1] += dp[i][j];
    }
}

void dfs2(int par, int node) {
    for (int i: adj[node]) if (i != par) {
        for (int j = K; j >= 1; --j) {
            dp[i][j] += dp[node][j-1];
            if (j != 1) dp[i][j] -= dp[i][j-2];
        }
        dfs2(node,i);
    }
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> K;
	F0R(i,N-1) {
	    int a,b; cin >> a >> b;
	    adj[a].pb(b), adj[b].pb(a);
	}
	FOR(i,1,N+1) cin >> dp[i][0];
	dfs1(0,1);
	dfs2(0,1);
    F0R(i,K) FOR(j,1,N+1) dp[j][i+1] += dp[j][i];
	FOR(i,1,N+1) cout << dp[i][K] << "\n";
}
