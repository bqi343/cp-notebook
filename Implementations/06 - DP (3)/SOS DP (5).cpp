/**
 * Description: if you add one to dp[0][i]
    * it adds one to dp[SZ][j] for all j s.t. (j&i) = j
 */

const int SZ = 20;

int dp[SZ+1][1<<SZ];

void prop() {
    F0R(i,SZ) F0R(j,1<<SZ) {
        dp[i+1][j] += dp[i][j];
        if (j&(1<<i)) dp[i+1][j^(1<<i)] += dp[i][j];
    }
}