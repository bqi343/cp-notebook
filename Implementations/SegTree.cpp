// http://codeforces.com/blog/entry/18051

#include <bits/stdc++.h>

using namespace std;

const int SZ = 1<<17;

struct SegTree {
	int seg[2*SZ];
	
	void upd(int p, int value) {  // set value at position p
  		for (seg[p += SZ] = value; p > 1; p >>= 1) seg[p>>1] = seg[p] + seg[p^1];
	}

	int qsum(int l, int r) {  // sum on interval [l, r)
	  	int res = 0;
	  	for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
	    	if (l&1) res += seg[l++];
	    	if (r&1) res += seg[--r];
	  	}
	  	return res;
	}
};

int main() {
	SegTree a;
	a.upd(0,10);
	a.upd(2,5);
	cout << a.qsum(0,3);
}
