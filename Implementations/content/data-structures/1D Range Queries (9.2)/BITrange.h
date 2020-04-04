/**
 * Description: $D$-dimensional range increment and sum query with $2^D$ BITs, case $D=1$
 * Source: https://www.geeksforgeeks.org/binary-indexed-tree-range-update-range-queries/
 * Verification: CSES
 * Time: O(\log N)
 */

#include "BIT (9.2).h"

template<class T, int SZ> struct BITrange {
	BIT<T,SZ> bit[2]; // piecewise linear functions
	// let cum[x] = sum_{i=1}^{x}a[i]
	void upd(int hi, T val) { // add val to a[1..hi]
		// if x <= hi, cum[x] += val*x
		bit[1].upd(1,val), bit[1].upd(hi+1,-val); 
		// if x > hi, cum[x] += val*hi
		bit[0].upd(hi+1,hi*val); 
	}
	void upd(int lo,int hi,T val){upd(lo-1,-val),upd(hi,val);}
	T sum(int x) { return bit[1].sum(x)*x+bit[0].sum(x); } 
	T query(int x, int y) { return sum(y)-sum(x-1); }
}; 
