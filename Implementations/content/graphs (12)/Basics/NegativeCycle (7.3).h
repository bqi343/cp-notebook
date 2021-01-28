/**
 * Description: use Bellman-Ford (make sure no underflow)
 * Source: https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html
 * Verification: https://cses.fi/problemset/task/1197/
 */

vi negCyc(int n, vector<pair<pi,int>> ed) {
	vl d(n); vi p(n); int x = -1;
	F0R(i,n) {
		x = -1; each(t,ed) if (ckmin(d[t.f.s],d[t.f.f]+t.s))
			p[t.f.s] = t.f.f, x = t.f.s;
		if (x == -1) return {};
	}
	F0R(i,n) x = p[x]; // enter cycle
	vi cyc = {x}; while (p[cyc.bk] != x) cyc.pb(p[cyc.bk]);
	reverse(all(cyc)); return cyc;
}

/**
Explanation:

If we follow the links back from t.f.s then we must always enter a cycle. 
Otherwise, this would contradict the assumption that there exists a shorter
path to t.f.s when considering paths of arbitrary length than those of 
length at most n-1. The sum of the edge weights along this path is
non-positive, and it can't be zero because then it would have no origin ...
*/
