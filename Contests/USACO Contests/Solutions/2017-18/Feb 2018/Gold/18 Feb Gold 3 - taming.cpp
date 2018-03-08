#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

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
const double PI = 4*atan(1);
const ll INF = 1e18;

int n, a[100], dp[100][101][100], ans[101]; // day, # breakouts, last breakout

int main() {
    // freopen("taming.in","r",stdin);
    // freopen("taming.out","w",stdout);
    
    cin >> n; F0R(i,n) cin >> a[i];
    
    F0R(i,n) FOR(j,1,n+1) F0R(k,n) dp[i][j][k] = MOD;
    dp[0][1][0] = (a[0] != 0);
    
    F0R(i,n-1) FOR(j,1,n+1) F0R(k,n) if (dp[i][j][k] != MOD) {
        dp[i+1][j][k] = min(dp[i+1][j][k],dp[i][j][k]+(a[i+1] != i+1-k));
        dp[i+1][j+1][i+1] = min(dp[i+1][j+1][i+1],dp[i][j][k]+(a[i+1] != 0));
    }
    
    FOR(i,1,n+1) ans[i] = MOD;
    FOR(j,1,n+1) F0R(k,n) ans[j] = min(ans[j],dp[n-1][j][k]);
    FOR(i,1,n+1) cout << ans[i] << "\n";
}

// read the question correctly (is y a vowel?)
// look out for special cases (n=1?) and overflow (ll vs int?)
