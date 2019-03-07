/**
 * Description: Classic DP example
 * Source: own
 * Verification: https://pcs.cs.cloud.vt.edu/problems/224
 */

int lcs(string a, string b) {
	vi dp(sz(b)+1);
	trav(c,a) {
	    F0Rd(i,sz(b)) if (b[i] == c) dp[i+1] = dp[i]+1;
	    F0R(i,sz(b)) ckmax(dp[i+1],dp[i]);
	}
	return dp[sz(b)];
}