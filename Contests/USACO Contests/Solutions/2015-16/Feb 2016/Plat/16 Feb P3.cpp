#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;
 
typedef long long ll;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)

#define pb push_back

ll inf = 1e18;
ll ans = inf, n, k, dp[1000][8];
vector<ll> cow, cum;

ll get(int low, int high) {
	if (low == 0) return dp[high][1];
	return dp[high][1]-dp[low-1][1]-low*(cum[high]-cum[low-1]);
}

void fill(int l, int r, int low, int high, int curk) {
	if (l>r) return;
	int mid = (l+r)/2, best = 0;
	dp[mid][curk] = inf;
	FOR(i,low,min(mid,high+1)) {
		if (dp[i][curk-1]+get(i+1,mid)<dp[mid][curk]) {
			dp[mid][curk] = dp[i][curk-1]+get(i+1,mid);
			best = i;
		}
	}
	fill(l,mid-1,low,best,curk);
	fill(mid+1,r,best,high,curk);
}

void dfs() { 
	F0R(i,n) {
		cum[i] = cow[i];
		if (i) cum[i] += cum[i-1];
	}
	
	dp[0][1] = 0;
	FOR(i,1,n) dp[i][1] = dp[i-1][1]+i*cow[i];
	FOR(j,2,k+1) fill(j-1,n-1,j-2,n-2,j);
	ans = min(ans,dp[n-1][k]);
}

int main() { 
	ifstream cin ("cbarn.in");
	ofstream cout ("cbarn.out");
	cin >> n >> k; cow.resize(n); cum.resize(n);
	F0R(i,n) cin >> cow[i];
	F0R(i,n) {
		dfs();
		cow.pb(cow[0]);
		cow.erase(cow.begin());
	}
	cout << ans;
}