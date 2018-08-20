#include<iostream>
#include<fstream>
#include<vector>

using namespace std;
 
typedef long long ll;
typedef pair <int, int> pi;
typedef vector<int> vi;

#define mp make_pair
#define pb push_back

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define endl "\n"

int N,X,Y,Z, dp[1001][1001];
vi A, B;

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> X >> Y >> Z;
	F0R(i,N) {
		int Ai, Bi; cin >> Ai >> Bi;
		F0R(j,Ai) A.pb(i);
		F0R(j,Bi) B.pb(i);
	}
	F0R(i,A.size()+1) dp[i][0] = i*Y;
	F0R(i,B.size()+1) dp[0][i] = i*X;
	FOR(i,1,A.size()+1) FOR(j,1,B.size()+1) {
		dp[i][j] = min(dp[i][j-1]+X,dp[i-1][j]+Y);
		dp[i][j] = min(dp[i][j],dp[i-1][j-1]+Z*abs(A[i-1]-B[j-1]));
	}
	cout << dp[A.size()][B.size()];
}
