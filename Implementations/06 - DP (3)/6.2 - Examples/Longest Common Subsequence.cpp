/**
* Description: Classic DP example
* Verification: https://pcs.cs.cloud.vt.edu/problems/224
*/

int lcs(string a, string b) {
	vi dp(sz(b)+1);
	for (char c: a) {
	    F0Rd(i,sz(b)) if (b[i] == c) dp[i+1] = dp[i]+1;
	    F0R(i,sz(b)) dp[i+1] = max(dp[i+1],dp[i]);
	}
	return dp[sz(b)];
}