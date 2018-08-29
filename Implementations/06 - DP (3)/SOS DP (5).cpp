/**
 * Description: if you add one to dp[i]
    * it adds one to result[j] for all j such that j&i = j
 */

vi sos (vi dp) {
    int SZ = 31-__builtin_clz(sz(dp)); // sz(dp) = 1<<SZ
    F0R(i,SZ) {
        vi res = dp;
        F0R(j,1<<SZ) if (j&(1<<i)) res[j^(1<<i)] += dp[j];
        swap(res,dp);
    }
    return dp;
}
