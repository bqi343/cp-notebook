#include<set>
#include<map>
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<cstring>
#include<algorithm>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef set<int> si;
typedef map<int,int> mii;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = b-1; i >= a; i--)
#define F0Rd(i,a) for (int i = a-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
 
const int MOD = 1000000007;
double PI = 4*atan(1);

// ifstream cin ("checklist.in");
// ofstream cout ("checklist.out");

int H,G;
vector<pi> H1, G1;

ll dp[1001][1001][2];

int dist(pi a, pi b) {
	return (a.s-b.s)*(a.s-b.s)+(a.f-b.f)*(a.f-b.f);
}

int main() {
	cin >> H >> G;
	H1.resize(H+1), G1.resize(G+1);
	FOR(i,1,H+1) cin >> H1[i].f >> H1[i].s;
	FOR(i,1,G+1) cin >> G1[i].f >> G1[i].s;
	
	memset(dp, 2*MOD, sizeof dp);
	dp[1][0][0] = 0;	
	FOR(i,2,H+1) dp[i][0][0] = dp[i-1][0][0]+dist(H1[i-1],H1[i]);
	dp[1][1][1] = dp[1][0][0]+dist(H1[1],G1[1]);
	FOR(j,2,G+1) dp[1][j][1] = dp[1][j-1][1]+dist(G1[j-1],G1[j]);

	FOR(i,2,H+1) FOR(j,1,G+1) {
		dp[i][j][0] = dp[i-1][j][1]+dist(H1[i],G1[j]);
		dp[i][j][0] = min(dp[i][j][0],dp[i-1][j][0]+dist(H1[i],H1[i-1]));
		dp[i][j][1] = dp[i][j-1][0]+dist(H1[i],G1[j]);
		dp[i][j][1] = min(dp[i][j][1],dp[i][j-1][1]+dist(G1[j-1],G1[j]));
	}
	cout << dp[H][G][0];
}
