/**
* Description: Bitset DP example
* Solves TSP for small N
*/

const int MX = 15;

int N, dp[MX][1<<MX], dist[MX][MX];

int solve() {
    F0R(i,N) F0R(j,1<<N) dp[i][j] = MOD;
    
    dp[0][1] = 0;
    F0R(j,1<<N) F0R(i,N) if (j&(1<<i)) 
        F0R(k,N) if (!(j&(1<<k))) 
            dp[k][j^(1<<k)] = min(dp[k][j^(1<<k)],
                                dp[i][j]+dist[i][k]);
        
    int ans = MOD;
    FOR(j,1,N) ans = min(ans,dp[j][(1<<N)-1]+dist[j][0]);
    return ans;
}