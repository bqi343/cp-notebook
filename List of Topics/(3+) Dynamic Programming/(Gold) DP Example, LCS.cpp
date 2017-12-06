int dp[1001][1001];
string a,b;

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> a >> b;
	F0R(i,a.length()) F0R(j,b.length()) {
	    dp[i+1][j+1] = max(dp[i+1][j],dp[i][j+1]);
	    if (a[i] == b[j]) dp[i+1][j+1] = max(dp[i+1][j+1],dp[i][j]+1);
	}
	cout << dp[a.length()][b.length()];
}