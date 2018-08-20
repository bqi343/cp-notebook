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

int N,L,dp[1<<20], ans = MOD;
vector<pair<int,set<int>>> movies;

int main() {
	ifstream cin ("movie.in");
	ofstream cout ("movie.out");
	cin >> N >> L;
	F0R(i,N) {
		int D,C; cin >> D >> C;
		set<int> cur;
		F0R(j,C) { int x; cin >> x; cur.insert(x); }
		movies.pb({D,cur});
	}
	F0R(i,1<<N) dp[i] = -1;
	F0R(i,1<<N) {
		int cur = 0;
		F0R(j,N) if (i & (1<<j)) {
			cur++;
			if (dp[i ^ (1<<j)] == -1) continue;
			auto x = movies[j].s.ub(dp[i ^ (1<<j)]);
			if (x == movies[j].s.begin()) continue;
			x = prev(x);
			dp[i] = max(dp[i],(*x)+movies[j].f);
		}
		dp[i] = min(dp[i],L);
		if (dp[i] == L) ans = min(ans,cur);
		if (i == 0) dp[i] = 0;
	}
	if (ans == MOD) cout << -1;
	else cout << ans;
}
