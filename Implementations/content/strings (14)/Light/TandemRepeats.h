/**
 * Description: Find all $(i,p)$ such that 
 	* \texttt{s.substr(i,p) == s.substr(i+p,p)}. No two intervals
 	* with the same period intersect or touch.
 * Time: O(N\log N)
 * Source: https://codeforces.com/gym/102012/submission/54638473
 * Verification: GP of Nanjing 2020 D - String Theory
 	* https://judge.yosupo.jp/problem/runenumerate
 */

#include "SuffixArray.h"

vector<array<int,3>> solve(str s) {
	int N = sz(s); SuffixArray A,B; 
	A.init(s); reverse(all(s)); B.init(s);
	vector<array<int,3>> runs;
	for (int p = 1; 2*p <= N; ++p) { // do in O(N/p) for period p
		for (int i = 0, lst = -1; i+p <= N; i += p) {
			int l = i-B.getLCP(N-i-p,N-i), r = i-p+A.getLCP(i,i+p);
			if (l > r || l == lst) continue;
			runs.pb({lst = l,r,p}); // for each i in [l,r],
		} // s.substr(i,p) == s.substr(i+p,p)
	}
	return runs;
} // ps(solve("aaabababa"));