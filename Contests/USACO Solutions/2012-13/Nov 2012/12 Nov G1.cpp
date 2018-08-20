#include <vector>
#include <cmath>
#include <fstream>
//#include <iostream>

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

int sum[1001], dp[1001][1001], N; // current pos, Holstein count
string s;

ifstream cin ("bbreeds.in");
ofstream cout ("bbreeds.out");

int main() {
	cin >> s; N = s.length();
	F0R(i,N) {
		if (s[i] == '(') sum[i] ++;
		else sum[i] --;
		if (i) sum[i] += sum[i-1];
	}
	dp[0][0] = dp[0][1] = 1;
	FOR(i,1,N) F0R(j,sum[i]+1) {
		if (s[i] == '(') {
			if (j) dp[i][j] += dp[i-1][j-1];
			dp[i][j] += dp[i-1][j]; 
		} else {
			if (j+1 <= 1000) dp[i][j] += dp[i-1][j+1];
			dp[i][j] += dp[i-1][j]; 
		}
		dp[i][j] %= 2012;
	}
	if (sum[0] == 1 && sum[N-1] == 0) cout << dp[N-1][0];
}
