// http://codeforces.com/blog/entry/18051

#include <bits/stdc++.h>

const int MOD = 1000000007;

using namespace std;

template<int SZ>
class SegSum {
	public:
		int seg[2*SZ];

		SegSum() {
			memset(seg,0,sizeof seg);	
		}

		void upd(int p, int value) {  // set value at position p
			for (seg[p += SZ] = value; p > 1; p >>= 1) seg[p>>1] = seg[p] + seg[p^1];
		}
		
		void build() {
			for (int i = SZ-1; i > 0; --i) seg[i] = seg[2*i]+seg[2*i+1];	
		}

		int query(int l, int r) {  // sum on interval [l, r)
			int res = 0;
			for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
				if (l&1) res += seg[l++];
				if (r&1) res += seg[--r];
			}
			return res;
		}
};


template<int SZ>
class SegMin {
	public:
		int seg[2*SZ];

		SegMin() {
			memset(seg,0,sizeof seg);	
		}
		
		void upd(int p, int value) {  // set value at position p
			for (seg[p += SZ] = value; p > 1; p >>= 1) seg[p>>1] = min(seg[p],seg[p^1]);
		}
		
		void build() {
			for (int i = SZ-1; i > 0; --i) seg[i] = min(seg[2*i],seg[2*i+1]);	
		}
		
		int query(int l, int r) {  // minimum on interval [l, r)
			int res = MOD;
			for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
				if (l&1) res = min(res,seg[l++]);
				if (r&1) res = min(res,seg[--r]);
			}
			return res;
		}
};

int main() {
	SegSum<1<<17> a;
	a.upd(0,10);
	a.upd(2,5);
	cout << a.query(0,3);
}
