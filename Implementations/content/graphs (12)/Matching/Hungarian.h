/**
 * Description: Given array of (possibly negative) costs to complete 
	* each of $N$ (1-indexed) jobs w/ each of $M$ workers $(N\le M)$, 
	* finds min cost to complete all jobs such that each worker is 
	* assigned to at most one job. Basically Dijkstra with potentials.
 * Time: O(N^2M)
 * Source: https://github.com/mpfeifer1/Kattis/blob/master/cordonbleu.cpp, tourist?
	* http://www.hungarianalgorithm.com/examplehungarianalgorithm.php
	* https://en.wikipedia.org/wiki/Hungarian_algorithm
	* https://www.geeksforgeeks.org/hungarian-algorithm-assignment-problem-set-1-introduction/
	* https://brilliant.org/wiki/hungarian-matching/
	* https://www.topcoder.com/community/competitive-programming/tutorials/assignment-problem-and-hungarian-algorithm/
 * Verification: https://www.spoj.com/problems/BABY/
	* also see https://codeforces.com/blog/entry/63701
 */

int hungarian(const vector<vi>& a) { 
	int N = sz(a)-1, M = sz(a[0])-1; assert(N <= M);
	vi u(N+1), v(M+1), p(M+1); // edge(i->j) >= u[i]+v[j]
	// p[j] -> job picked by worker j
	FOR(i,1,N+1) { // find alternating path with job i
		int j0; p[j0 = 0] = i; // add "dummy" worker 0
		vi dist(M+1,INT_MAX), pre(M+1,-1); vector<bool> done(M+1);
		while (p[j0]) { // dijkstra
			done[j0] = 1; int i0 = p[j0], j1, delta = INT_MAX; 
			// fix dist[j0], update dists from j0
			FOR(j,1,M+1) if (!done[j]) {
				if (ckmin(dist[j],a[i0][j]-u[i0]-v[j])) pre[j] = j0;
				if (ckmin(delta,dist[j])) j1 = j;
			}
			F0R(j,M+1) { // subtract constant from all edges going 
				// from done -> not done vertices, lowers all 
				// remaining dists by constant
				if (done[j]) u[p[j]] += delta, v[j] -= delta; 
				else dist[j] -= delta; 
			}
			j0 = j1; // j1 must be initialized
		} // Potentials adjusted so all edge weights >= 0.
		// Perfect matching has zero weight and
		// costs of augmenting paths do not change.
		while (j0) { int j1 = pre[j0]; p[j0] = p[j1]; j0 = j1; }
	} // p[j0] = 0, found alternating path 
	return -v[0]; // min cost
}