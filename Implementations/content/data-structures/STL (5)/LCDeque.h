/**
 * Description: LineContainer given assumptions
 * Time: O(1)
 * Source: Own
 * Verification: http://acm.hdu.edu.cn/diy/contest_showproblem.php?cid=36005&pid=1009
 */

#include "LineContainer.h"

struct LC0 : deque<Line> { 
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
	void add(ll k, ll m) { // line goes to one end of deque
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
			while (size() > 1 && prev(prev(end()))->p >= x) 
				pop_back();
			return back().eval(x);
		}
	}	
};
