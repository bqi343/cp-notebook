/**
 * Description: DP with Binary Search
 * Source: own
 * Verification: https://cses.fi/problemset/task/1145/
 */

int lis(vi v) {
	vi min_last{INT_MIN}; // min last term of increasing sequence with i terms
	for (int x: v) {
		int lo = lb(all(min_last),x)-begin(min_last);
		if (lo == sz(min_last)) min_last.pb(0);
		min_last[lo] = x;
	}
	return sz(min_last)-1;
}