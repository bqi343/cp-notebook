/**
* Description: Classic DP example
*/

int dp[1001][1001];
string a,b;

int main() {
	cin >> a >> b;
	F0R(i,sz(a)) F0R(j,b.sz(b)) {
	    dp[i+1][j+1] = max(dp[i+1][j],dp[i][j+1]);
	    if (a[i] == b[j]) dp[i+1][j+1] = max(dp[i+1][j+1],dp[i][j]+1);
	}
	cout << dp[sz(a)][sz(b)];
}