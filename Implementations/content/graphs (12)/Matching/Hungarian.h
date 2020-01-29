/**
 * Description: Given array of (possibly negative) costs to complete 
 	* each of $N$ jobs w/ each of $M$ workers $(N\le M)$, finds min cost to 
 	* complete all jobs such that each worker is assigned to at most one job.
 	* Basically just Dijkstra with potentials.
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
	int n = sz(a)-1, m = sz(a[0])-1; // jobs 1..n, workers 1..m
	vi u(n+1), v(m+1); // potentials
	vi p(m+1); // p[j] -> job picked by worker j
	FOR(i,1,n+1) { // find alternating path with job i
		p[0] = i; int j0 = 0; // add "dummy" worker 0
		vi dist(m+1,INT_MAX), pre(m+1,-1); 
		vector<bool> done(m+1, false);
		do { // dijkstra
			done[j0] = true; // fix dist[j0], update dists from j0
			int i0 = p[j0], j1; int delta = INT_MAX;
			FOR(j,1,m+1) if (!done[j]) { 
				auto cur = a[i0][j]-u[i0]-v[j]; 
				if (ckmin(dist[j],cur)) pre[j] = j0;
				if (ckmin(delta,dist[j])) j1 = j;
			}
			F0R(j,m+1) { // subtract constant from all edges going 
				// from done -> not done vertices, lowers all 
				// remaining dists by constant
				if (done[j]) u[p[j]] += delta, v[j] -= delta; 
				else dist[j] -= delta; 
			}
			j0 = j1;
		} while (p[j0]); // Potentials adjusted so all edge weights 
		// are non-negative. Perfect matching has zero weight and
		// costs of augmenting paths do not change.
		while (j0) { // update alternating path
			int j1 = pre[j0];
			p[j0] = p[j1]; j0 = j1;
		} 
	}
	return -v[0]; // min cost
}
