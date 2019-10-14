/**
 * Description: solves knapsack in pseudo-polynomial time
 * Source: Own
 * Verification: https://open.kattis.com/problems/knapsack
 */

vi solve(int cap, vi v, vi w) {
	vi dp[sz(v)+1]; dp[0].resz(cap+1);
    F0R(i,sz(v)) {
		dp[i+1] = dp[i];
        F0R(j,cap+1-w[i]) ckmax(dp[i+1][w[i]+j],dp[i][j]+v[i]);
    }
    vi ans; R0F(i,sz(v)) if (dp[i][cap] != dp[i+1][cap]) cap -= w[i], ans.pb(i);
    return ans;
}
