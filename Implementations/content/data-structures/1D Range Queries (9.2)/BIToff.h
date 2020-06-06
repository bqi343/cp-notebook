/**
 * Description: Offline BIT with coordinate copmpression. First do all 
   * updates with $\texttt{mode=0}$ and then call $\texttt{init()}$.
 * Source: Own
 * Verification: https://codeforces.com/contest/1361/problem/F
 */

template<class T> struct BIToff {
	bool mode = 0; vi v; vector<T> d;
	int atMost(int x) { return ub(all(v),x)-begin(v); } // how many <= x
	void upd(int x, T y) {
		if (!mode) { v.pb(x); return; }
		int p = atMost(x); assert(p && v[p-1] == x);
		for (;p<=sz(v);p+=p&-p) d[p] += y;
	}	
	void init() { assert(!mode); mode = 1;
		sort(all(v)); v.erase(unique(all(v)),end(v)); d.rsz(sz(v)+1); }
	T sum(int x) { assert(mode);
		T ans = 0; for (int p=atMost(x);p;p-=p&-p) ans += d[p];
		return ans; }
	T query(int x, int y) { return sum(y)-sum(x-1);}
};