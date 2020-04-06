/**
 * Description: Computes $S(\sigma)$ in Schensted's algorithm. 
 	* All elements of $A$ should be distinct.
 * Source: Mark Gordon - https://gist.github.com/msg555/4242182
 	* proof - https://books.google.com/books?hl=en&lr=&id=8uTMBQAAQBAJ&oi=fnd&pg=PA39&dq=+An+extension+of+Schensted%E2%80%99s+theorem&ots=GUiiGZFPVG&sig=JHTgu4N3-npZNnqCMwdRQTrXhfE#v=onepage&q=An%20extension%20of%20Schensted%E2%80%99s%20theorem&f=false
	* https://en.wikipedia.org/wiki/Robinson%E2%80%93Schensted%E2%80%93Knuth_correspondence
	* https://codeforces.com/blog/entry/16499?#comment-214121
 * Time: O(N^2) with naive, O(N\sqrt N\log N) with \texttt{fastRsk}.
 * Verification: ?
 */

/*Ex. \sigma=(5,2,3,1,4)
S(\sigma) = 5 -> 2 -> 2 3 -> 1 3 -> 1 3 4
                 5 -> 5      2      2
                             5      5
T(\sigma) = 1 -> 1 -> 1 3 -> 1 3 -> 1 3 5
                 2    2      2      2
                             4      4
*/
vector<vi> boundedRsk(const vi& A, int k) {
	vector<vi> h(k);
	F0R(i,sz(A)) {
		int x = A[i];
		F0R(j,k) {
			int p = lb(all(h[j]),x)-begin(h[j]);
			if (p == sz(h[j])) { h[j].pb(x); break; }
			swap(x,h[j][p]);
		}
	}
	return h;
}
vector<vi> fastRsk(vi A) {
	int rtn = (int)ceil(sqrt(sz(A)));
	auto ha = boundedRsk(A, rtn);
	reverse(all(A)); auto hb = boundedRsk(A, rtn);
	ha.rsz(sz(hb[0]));
	FOR(i,rtn,sz(hb[0])) for (int j = 0; i < sz(hb[j]); j++)
		ha[i].pb(hb[j][i]);
	return ha;
}