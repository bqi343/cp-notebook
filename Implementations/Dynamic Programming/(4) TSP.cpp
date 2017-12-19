/**
* Source: own
* Description: Example of bitset DP
*/

const int MX = 18;
const double INF = 1e18;

double dp[MX][1<<MX], dist[MX][MX];

double solve() {
    F0R(i,MX) F0R(j,1<<MX) dp[i][j] = INF;
    
    dp[0][1] = 0;
    F0R(j,1<<MX) F0R(i,MX) if (j&(1<<i)) 
        F0R(k,MX) if (!(j&(1<<k))) 
            dp[k][j^(1<<k)] = min(dp[k][j^(1<<k)],dp[i][j]+dist[i][k]);
        
    double ans = INF;
    FOR(j,1,MX) ans = min(ans,dp[j][(1<<MX)-1]+dist[j][0]);
    return ans;
}