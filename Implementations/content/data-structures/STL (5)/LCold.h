/**
 * Description: LineContainer; add lines of the form $kx+m$, 
 	* compute greatest $y$-coordinate for any $x$.
 * Time: O(\log N)
 * Source: KACTL
   * https://github.com/kth-competitive-programming/kactl/commit/165807e28402c9be906f6e6a09452431787bb70d?diff=unified
 * Verification: 
   * CSA Squared Ends not working :(
   * https://codeforces.com/contest/1083/problem/E
   * https://atcoder.jp/contests/arc066/tasks/arc066_d
 */

bool Q;
struct Line {
	mutable ll k, m, p; // slope, y-intercept, last optimal x
	ll eval (ll x) { return k*x+m; }
	bool operator<(const Line& o) const { return Q?p<o.p:k<o.k; }
};

// for doubles, use inf = 1/.0, divi(a,b) = a/b
const ll inf = LLONG_MAX;
// floored div
ll divi(ll a, ll b) { return a/b-((a^b) < 0 && a%b); } 
// last x such that first line is better
ll bet(const Line& x, const Line& y) { 
	if (x.k == y.k) return x.m >= y.m ? inf : -inf;
	return divi(y.m-x.m,x.k-y.k); }

struct LC : multiset<Line> { 
	// updates x->p, determines if y is unneeded
	bool isect(iterator x, iterator y) { 
		if (y == end()) { x->p = inf; return 0; }
		x->p = bet(*x,*y); return x->p >= y->p; }
	void add(ll k, ll m) {
		auto z = insert({k,m,0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) 
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		Q = 1; auto l = *lb({0,0,x}); Q = 0;
		return l.k*x+l.m;
	}
};