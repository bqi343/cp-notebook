/**
 * Description: 1D point update, range query
 * Time: O(\log N)
 * Source: 
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 */

template<class T> struct Seg { 
	const T ID = 0; // comb(ID,b) must equal b
	T comb(T a, T b) { return a+b; } // easily change this to min or max
	int n; vector<T> seg;
	void init(int _n) { n = _n; seg.rsz(2*n); }

	void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T value) {	// set value at position p
		seg[p += n] = value;
		for (p /= 2; p; p /= 2) pull(p);
	}

	T query(int l, int r) {	 // sum on interval [l, r]
		T ra = ID, rb = ID; // make sure non-commutative operations work
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra,seg[l++]);
			if (r&1) rb = comb(seg[--r],rb);
		}
		return comb(ra,rb);
	}
};