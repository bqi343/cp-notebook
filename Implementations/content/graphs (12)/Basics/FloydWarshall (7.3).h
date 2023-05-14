/**
 * Description: All-Pairs Shortest Path
 * Source: KACTL
 * Verification: 
    * https://open.kattis.com/problems/allpairspath
    * https://cses.fi/problemset/task/1672/
 */

void floydWarshall(V<vl>& m) {
    int n = sz(m);
    F0R(i,n) ckmin(m[i][i], 0LL);
    F0R(k,n) F0R(i,n) F0R(j,n)
        if (m[i][k] != BIG && m[k][j] != BIG) {
            auto newDist = max(m[i][k]+m[k][j],-BIG);
            ckmin(m[i][j],newDist);
        }
    F0R(k,n) if (m[k][k] < 0) F0R(i,n) F0R(j,n)
        if (m[i][k] != BIG && m[k][j] != BIG) m[i][j] = -BIG;
}