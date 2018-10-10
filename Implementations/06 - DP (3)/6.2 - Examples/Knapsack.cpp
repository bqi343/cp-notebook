/**
* Description: solves knapsack in pseudo-polynomial time
* Verification: https://open.kattis.com/problems/knapsack
*/

const int MX = 2001;

vi solve(int cap, vi v, vi w) {
	int dp[MX][MX]; F0R(i,cap+1) dp[0][i] = 0;

    F0R(i,sz(v)) {
        F0R(j,cap+1) dp[i+1][j] = dp[i][j];
        F0R(j,cap+1) if (w[i]+j <= cap) dp[i+1][w[i]+j] = max(dp[i+1][w[i]+j],dp[i][j]+v[i]);
    }
    
    vi ans; 
    F0Rd(i,sz(v)) if (dp[i][cap] != dp[i+1][cap]) cap -= w[i], ans.pb(i);
    return ans;
}