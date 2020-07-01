/**
 * Description: LineContainer; add lines of the form $ax+b$, 
 	* compute greatest $y$-coordinate for any $x$.
 * Time: O(\log N)
 * Source: KACTL
   * https://github.com/kth-competitive-programming/kactl/commit/165807e28402c9be906f6e6a09452431787bb70d?diff=unified
 * Verification: https://judge.yosupo.jp/problem/line_add_get_min
 */


const ll inf = LLONG_MAX; bool _Q;
ll fdiv(ll a, ll b) { return a/b-((a^b) < 0 && a%b); } // works for all b!=0
struct Line { // a and b -> slope and y-intercept 
	mutable ll a, b, lst; // lst can change
	ll eval(ll x) const { return a*x+b; }
	bool operator<(const Line& y) const { return _Q?lst<y.lst:a<y.a; }
	/// friend str ts(const Line& L) { return ts(vl{L.a,L.b,L.lst}); }
	ll bet(const Line& y) const { assert(a <= y.a);
		return a == y.a ? (b >= y.b ? inf : -inf) : fdiv(b-y.b,y.a-a); }
};

struct LC : multiset<Line> {
	bool rem(iterator IT) { auto it = IT++; // update lst for it
		if (IT == end()) return it->lst = inf, 0;
		return (it->lst = it->bet(*IT)) >= IT->lst; }
	void add(ll a, ll b) { // y -> inserted pos
		auto z = insert({a,b,0}), y = z++, x = y; 
		while (rem(y)) erase(z++); /// remove stuff after insertion pos
		if (x != begin() && rem(--x)) erase(y), rem(x); /// remove inserted line
		while ((y = x) != begin() && (--x)->lst >= y->lst) erase(y), rem(x); /// remove stuff before insertion pos
	}
	ll query(ll p) { 
		assert(size()); _Q = 1; 
		ll ret = lb({0,0,p})->eval(p); _Q = 0; return ret; }
};