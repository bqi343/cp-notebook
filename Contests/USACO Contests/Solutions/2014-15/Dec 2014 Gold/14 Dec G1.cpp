// #include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<unordered_map>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>

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

ll N,H,ans=-1;
vector<pair<pair<ll,ll>,ll>> cows; // height, weight, strength
pair<pair<ll,ll>,ll> dp[1<<20]; // height, weight, safety

int main() {
	ifstream cin ("guard.in");
	ofstream cout ("guard.out");
	cin >> N >> H; cows.resize(N);
	F0R(i,N) cin >> cows[i].f.f >> cows[i].f.s >> cows[i].s;
	F0R(i,1<<N) {
		dp[i].s = -1;
		F0R(j,N) if (i & (1<<j)) {
			int temp = i ^(1<<j);
			if (dp[temp].s != -1) if (cows[j].s >= dp[temp].f.s) 
				dp[i].s = max(dp[i].s,min(dp[temp].s,cows[j].s-dp[temp].f.s));
			dp[i].f.f += cows[j].f.f, dp[i].f.s += cows[j].f.s;
		}
		if (i == 0) dp[i].s = MOD;
		if (dp[i].f.f >= H) ans = max(ans,dp[i].s);
	}
	if (ans == -1) cout << "Mark is too tall";
	else cout << ans;
}
