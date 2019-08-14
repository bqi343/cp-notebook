/**
 * Description: finds min cost to complete n jobs w/ m workers 
	* each worker is assigned to at most one job (n <= m)
 * Source: https://github.com/mpfeifer1/Kattis/blob/master/cordonbleu.cpp
 * Verification: https://www.spoj.com/problems/BABY/
    * also see https://codeforces.com/blog/entry/63701
 */

int HungarianMatch(const vector<vi>& a) { 
    int n = sz(a)-1, m = sz(a[0])-1; // jobs 1..n, workers 1..m
    vi u(n+1), v(m+1), p(m+1), way(m+1); // p[j] -> job picked by worker j
    FOR(i,1,n+1) { // find alternating path with job i
        p[0] = i; int j0 = 0;
        vi minv(m+1, MOD);
        vector<bool> used(m+1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1; int delta = MOD;
            FOR(j,1,m+1) if (!used[j]) {
                auto cur = a[i0][j]-u[i0]-v[j];
                if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                if (minv[j] < delta) delta = minv[j], j1 = j;
            }
            F0R(j,m+1) // basically dijkstra with potentials??
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                else minv[j] -= delta;
            j0 = j1;
        } while (p[j0]);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    return -v[0];
}