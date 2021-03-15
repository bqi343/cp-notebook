/**
 * Description: 1D point update, range query where \texttt{comb} is
 	* any associative operation. If $N=2^p$ then \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source: 
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 */

template<class T> struct Seg { // comb(ID,b) = b
	const T ID = 0; T comb(T a, T b) { return a+b; } 
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2; 
		seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// any associative op on interval [l, r]
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra,seg[l++]);
			if (r&1) rb = comb(seg[--r],rb);
		}
		return comb(ra,rb);
	}
	int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
		if (r < lo || val > seg[ind]) return -1;
		if (l == r) return l;
		int m = (l+r)/2;
		int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
		return first_at_least(lo,val,2*ind+1,m+1,r);
	}
};
