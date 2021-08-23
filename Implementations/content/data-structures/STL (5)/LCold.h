/**
 * Description: Add lines of the form $ax+b$, 
 	* query maximum $y$-coordinate for any $x$.
 * Time: O(\log N)
 * Source: KACTL
   * https://github.com/kth-competitive-programming/kactl/commit/165807e28402c9be906f6e6a09452431787bb70d?diff=unified
 * Verification: https://judge.yosupo.jp/problem/line_add_get_min
 */

using T = ll; const T INF = LLONG_MAX; // a/b rounded down
// ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); }

bool _Q = 0;
struct Line {
	T a, b; mutable T lst;
	/// friend str ts(const Line& L) { return ts(vl{L.a,L.b,L.lst}); }
	T eval(T x) const { return a*x+b; }
	bool operator<(const Line&o)const{return _Q?lst<o.lst:a<o.a;}
	T last_gre(const Line& o) const { assert(a <= o.a); 
		// greatest x s.t. a*x+b >= o.a*x+o.b
		return lst=(a==o.a?(b>=o.b?INF:-INF):fdiv(b-o.b,o.a-a));}
};

struct LineContainer: multiset<Line> {
	bool isect(iterator it) { auto n_it = next(it);
		if (n_it == end()) return it->lst = INF, 0;
		return it->last_gre(*n_it) >= n_it->lst; }
	void add(T a, T b) { // remove lines after
		auto it = ins({a,b,0}); while (isect(it)) erase(next(it));
		if (it == begin()) return;
		if (isect(--it)) erase(next(it)), isect(it);
		while (it != begin()) { // remove lines before
			--it; if (it->lst < next(it)->lst) break;
			erase(next(it)); isect(it); }
	}
	T qmax(T x) { assert(!empty()); 
		_Q = 1; T res = lb({0,0,x})->eval(x); _Q = 0;
		return res; }
};