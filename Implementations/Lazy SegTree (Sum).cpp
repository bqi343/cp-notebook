#include <bits/stdc++.h>
 
using namespace std;

typedef long long ll;

const int SZ = 1<<20;
const ll INF = 1e18;

struct LazySegTree { 
	ll sum[2*SZ], lazy[2*SZ]; 
	
	LazySegTree() {
		memset (sum,0,sizeof sum);
		memset (lazy,0,sizeof lazy);
	}
	
	void push(int ind, int L, int R) {
	    sum[ind] += (R-L+1)*lazy[ind];
	    if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
	    lazy[ind] = 0;
	}
	 
	void pull(int ind) {
	    sum[ind] = sum[2*ind]+sum[2*ind+1];
	}
	 
	ll qsum(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
		push(ind,L,R);
	    if (lo > R || L > hi) return 0;
	    if (lo <= L && R <= hi) return sum[ind];
	    
	    int M = (L+R)/2;
	    return qsum(lo,hi,2*ind,L,M)+qsum(lo,hi,2*ind+1,M+1,R);
	}
	 
	void upd(int lo, int hi, int inc, int ind = 1, int L = 0, int R = SZ-1) { // take account for minimum as well
	    push(ind,L,R);
	    if (hi < L || R < lo) return;
	    if (lo <= L && R <= hi) {
	        lazy[ind] = inc;
	        push(ind,L,R);
	        return;
	    }
	    
	    int M = (L+R)/2;
	    upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
	    pull(ind);
	}
};
 
int main() {
	LazySegTree seg;
	seg.upd(0,5,2);
	seg.upd(5,7,3);
	cout << seg.qsum(4,6) << "\n";
}
