/**
 * Description: BIT of indexed sets (or treaps). $x\in (0,SZ)$.
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
	int query(int lox, int hix, int loy, int hiy) { 
		return query(hix,hiy)-query(lox-1,hiy)
			-query(hix,loy-1)+query(lox-1,loy-1); }
};