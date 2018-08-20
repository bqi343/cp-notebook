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

ifstream cin ("necklace.in");
ofstream cout ("necklace.out");

string N,M;
int nex[1000][26], dp[10001][1001]; // current pos, prefix

int main() {
	cin >> N >> M;
	FOR(i,1,M.size()+1) 
		FOR(j,i-1,M.size()) 
			if (M.substr(j-i+1,i-1) == M.substr(0,i-1)) 
				nex[j][M[i-1]-'a'] = i;
				
	F0R(i,N.length()+1) F0R(j,M.length()) dp[i][j] = MOD;
	dp[0][0] = 0;
	F0R(i,N.length()) F0R(j,M.length()) {
		dp[i+1][nex[j][N[i]-'a']] = min(dp[i+1][nex[j][N[i]-'a']],dp[i][j]);
		dp[i+1][j] = min(dp[i+1][j],dp[i][j]+1);
	}
	int ans = MOD;
	F0R(i,M.length()) ans = min(ans,dp[N.length()][i]);
	cout << ans;
}
