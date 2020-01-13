/**
 * Description: BIT of SegTrees. $x\in (0,SZ), y\in [0,SZ)$.
 * Memory: O(N\log^2 N)
 * Source: USACO Mowing the Field
 * Verification: 
 	* USACO Mowing the Field
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=722 (13/15, 15/15 and 1857ms with BumpAllocator)
 */

#include "../1D Range Queries (9.2)/SparseSeg (9.2).h"

template<class T> struct BITseg {
	node<T> seg[SZ];
	BITseg() { F0R(i,SZ) seg[i] = node<T>(); }
	void upd(int x, int y, int v) { // add v
		for (; x < SZ; x += x&-x) seg[x].upd(y,v); }
	T query(int x, int y1, int y2) {
		T res = 0; for (; x; x-=x&-x) res += seg[x].query(y1,y2);
		return res; }
	T query(int x1, int x2, int y1, int y2) { // query sum of rectangle
		return query(x2,y1,y2)-query(x1-1,y1,y2); }
};
