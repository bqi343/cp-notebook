/**
 * Description: BIT of indexed sets (or treaps). $x\in (0,SZ)$.
 	* Only supports setting value at each point to $0$ or $1$.
 * Memory: O(N\log N)
 * Verification: 
 	* http://codeforces.com/contest/785/submission/33953058
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=722 (13/15)
 */

#include "../STL (5)/IndexedSet.h"

template<int SZ> struct BITtree { 
	Tree<pi> val[SZ]; 
	void upd(int x, int y, int t = 1) { 
		for (int X = x; X < SZ; X += X&-X) {
			if (t == 1) val[X].insert({y,x});
			else val[X].erase({y,x});
		}
	}
	int query(int x, int y) { 
		int res = 0; for (; x; x -= x&-x) res += val[x].ook({y,MOD});
		return res;
	}
	int query(int xl, int xr, int yl, int yr) { 
		return query(xr,yr)-query(xl-1,yr)
			-query(xr,yl-1)+query(xl-1,yl-1); }
};
