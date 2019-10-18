/**
 * Description: finds min cost to complete n jobs w/ m workers 
	* each worker is assigned to at most one job (n <= m)
 * Time: ?
 * Source: https://github.com/mpfeifer1/Kattis/blob/master/cordonbleu.cpp
 * Verification: https://www.spoj.com/problems/BABY/
	* also see https://codeforces.com/blog/entry/63701
 */

int HungarianMatch(const vector<vi>& a) { // cost array, negative values are ok
	int n = sz(a)-1, m = sz(a[0])-1; // jobs 1..n, workers 1..m
	vi u(n+1), v(m+1), p(m+1); // p[j] -> job picked by worker j
	FOR(i,1,n+1) { // find alternating path with job i
		p[0] = i; int j0 = 0;
		vi dist(m+1, MOD), pre(m+1,-1); // dist, previous vertex on shortest path
		vector<bool> done(m+1, false);
		do {
			done[j0] = true;
			int i0 = p[j0], j1; int delta = MOD;
			FOR(j,1,m+1) if (!done[j]) {
				auto cur = a[i0][j]-u[i0]-v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			F0R(j,m+1) // just dijkstra with potentials
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			j0 = j1;
		} while (p[j0]);
		do { // update values on alternating path
			int j1 = pre[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}
	return -v[0]; // min cost
}