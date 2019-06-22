/**
 * Description: Given set of lines, computes the greatest y-coordinate for any x
 * Source: KACTL
 * Verification: 
   * CSA Squared Ends
   * https://atcoder.jp/contests/arc066/tasks/arc066_d
 */

bool Q;
struct Line {
	mutable ll k, m, p; // slope, y-intercept, last optimal x
	ll eval (ll x) { return k*x+m; }
	bool operator<(const Line& o) const { return Q ? p < o.p : k < o.k; }
};

struct LC : multiset<Line> { 
	// for doubles, use inf = 1/.0, div(a,b) = a/b
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { return a/b-((a^b) < 0 && a%b); } // floored division
	ll bet(const Line& x, const Line& y) { // last x such that first line is better
		if (x.k == y.k) return x.m >= y.m ? inf : -inf;
		return div(y.m-x.m,x.k-y.k);
	}
	bool isect(iterator x, iterator y) { // updates x->p, determines if y is unneeded
		if (y == end()) { x->p = inf; return 0; }
		x->p = bet(*x,*y); return x->p >= y->p;
	}
	
	void add(ll k, ll m) {
		auto z = insert({k,m,0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	
	ll query(ll x) { 
		assert(!empty());
		Q = 1; auto l = *lb({0,0,x}); Q = 0;
		return l.eval(x);
	}
};

struct LC0 : deque<Line> { // linear time w/ additional assumptions
	// for doubles, use inf = 1/.0, div(a,b) = a/b
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { return a/b-((a^b) < 0 && a%b); } // floored division
	ll bet(const Line& x, const Line& y) { // last x such that first line is better
		if (x.k == y.k) return x.m >= y.m ? inf : -inf;
		return div(y.m-x.m,x.k-y.k);
	}
	
	void addBack(Line L) { // assume nonempty
		while (1) {
			auto a = back(); pop_back(); a.p = bet(a,L);
			if (size() && back().p >= a.p) continue;
			pb(a); break;
		}
		L.p = inf; pb(L);
	}
	void addFront(Line L) {
		while (1) {
			if (!size()) { L.p = inf; break; }
			if ((L.p = bet(L,front())) >= front().p) pop_front();
			else break;
		}
		push_front(L);
	}
	void add(ll k, ll m) { // assume line goes to one end of deque
		if (!size() || k <= front().k) addFront({k,m,0});
		else assert(k >= back().k), addBack({k,m,0});
	}
	
	int ord = 0; // 1 = increasing, -1 = decreasing
	ll query(ll x) { 
		assert(ord);
		if (ord == 1) { 
			while (front().p < x) pop_front();
			return front().eval(x);
		} else {
			while (size() > 1 && prev(prev(end()))->p >= x) pop_back();
			return back().eval(x);
		}
	}	
};
