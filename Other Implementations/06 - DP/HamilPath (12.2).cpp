/**
 * Description: computes number of paths from N-2 to N-1 which 
 	* pass through each of the cities 0 to N-1 exactly once, mod 10^9+7
 * Time: O(N^22^N)
 * Source: own
 * Verification: CSES Hamiltonian Flights
 	* https://cses.fi/problemset/task/1690/
 */

int N;
bool adj[20][20];
mi dp[18][1<<18];

mi solve() {
    F0R(i,N-2) if (adj[N-2][i]) dp[i][1<<i] = 1;
    F0R(j,1<<(N-2)) F0R(i,N-2) if (j&(1<<i)) 
        F0R(k,N-2) if (!(j&(1<<k)) && adj[i][k]) 
            dp[k][j^(1<<k)] += dp[i][j];
    mi tot = 0; 
    F0R(i,N-2) if (adj[i][N-1]) tot += dp[i][(1<<(N-2))-1];
    return tot;
}