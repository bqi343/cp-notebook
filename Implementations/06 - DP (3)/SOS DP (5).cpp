/**
 * Description: if you add one to dp[i]
    * it adds one to dp[j] for all j such that j&i = j
 */

void sos (vi& dp, int x = 1) { // x = -1 reverses
    int SZ = 31-__builtin_clz(sz(dp));
    F0R(i,SZ) F0R(j,1<<SZ) if (j&(1<<i)) 
        dp[j^(1<<i)] += x*dp[j];
}