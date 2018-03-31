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

ifstream cin ("cowrun.in");
ofstream cout ("cowrun.out");

ll dp[1001][1001][2];
vi p1, p2;
// # of left cows done, # of right cows done, cpos

int main() {
	int N; cin >> N;
	F0R(i,N) {
		int p; cin >> p;
		if (p<0) p1.pb(p);
		else p2.pb(p);
	}
	F0R(i,1001) F0R(j,1001) F0R(k,2) dp[i][j][k] = 1e18;
	sort(p1.begin(),p1.end());
	p1.pb(0);
	reverse(p1.begin(),p1.end());
	p2.pb(0);
	sort(p2.begin(),p2.end());
	
	int x = p1.size()-1, y = p2.size()-1;
	F0R(i,x+1) F0R(j,y+1) {
		if (i == 0 && j == 0) {
			dp[0][1][1] = (x+y)*p2[1];
			dp[1][0][0] = -(x+y)*p1[1];
			continue;
		}
		if (i>0) {
			if (i<x) dp[i+1][j][0] = 
				min(dp[i+1][j][0],(x+y-i-j)*abs(p1[i+1]-p1[i])+dp[i][j][0]);
			if (j<y) dp[i][j+1][1] = 
				min(dp[i][j+1][1],(x+y-i-j)*abs(p2[j+1]-p1[i])+dp[i][j][0]);
		}
		if (j>0) {
			if (i<x) dp[i+1][j][0] = 
				min(dp[i+1][j][0],(x+y-i-j)*abs(p1[i+1]-p2[j])+dp[i][j][1]);
			if (j<y) dp[i][j+1][1] = 
				min(dp[i][j+1][1],(x+y-i-j)*abs(p2[j+1]-p2[j])+dp[i][j][1]);
		}
	}
	cout << min(dp[x][y][0],dp[x][y][1]);
}
