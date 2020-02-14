/**
 * Description: LineContainer assuming both slopes and queries monotonic.
 * Time: O(1)
 * Source: Own
 * Verification: http://acm.hdu.edu.cn/diy/contest_showproblem.php?cid=36005&pid=1009
 */

#include "LCold.h"

struct LCdeque : deque<Line> { 
	void addBack(Line L) { // assume nonempty
		while (1) {
			auto a = bk; pop_back(); a.p = bet(a,L);
			if (size() && bk.p >= a.p) continue;
			pb(a); break;
		}
		L.p = inf; pb(L);
	}
	void addFront(Line L) {
		while (1) {
			if (!size()) { L.p = inf; break; }
			if ((L.p = bet(L,ft)) >= ft.p) pop_front();
			else break;
		}
		push_front(L);
	}
	void add(ll k, ll m) { // line goes to one end of deque
		if (!size() || k <= ft.k) addFront({k,m,0});
		else assert(k >= bk.k), addBack({k,m,0});
	}
	int ord = 0; // 1 = increasing, -1 = decreasing
	ll query(ll x) { 
		assert(ord);
		if (ord == 1) { 
			while (ft.p < x) pop_front();
			return ft.eval(x);
		} else {
			while(size()>1&&prev(prev(end()))->p>=x)pop_back();
			return bk.eval(x);
		}
	}	
};
