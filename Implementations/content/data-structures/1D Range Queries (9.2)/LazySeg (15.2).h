/**
 * Description: 1D range update and query, $SZ=2^p$.
 * Source: USACO Counting Haybales
 * Verification: SPOJ Horrible
 */

template<class T, int SZ> struct LazySeg { 
	T sum[2*SZ], lazy[2*SZ]; 
	LazySeg() { F0R(i,2*SZ) sum[i] = lazy[i] = 0; }
	void push(int ind, int L, int R) { /// modify values for current node
		if (L != R) F0R(i,2) lazy[2*ind+i] += lazy[ind]; /// prop to children
		sum[ind] += (R-L+1)*lazy[ind]; lazy[ind] = 0; 
	} // recalc values for current node
	void pull(int ind) { sum[ind] = sum[2*ind]+sum[2*ind+1]; }
	void build() { ROF(i,1,SZ) pull(i); }
	void upd(int lo,int hi,T inc,int ind=1,int L=0, int R=SZ-1) {
		push(ind,L,R); if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) { 
			lazy[ind] = inc; push(ind,L,R); return; }
		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M); 
		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);
	}
	T qsum(int lo, int hi, int ind=1, int L=0, int R = SZ-1) {
		push(ind,L,R); if (lo > R || L > hi) return 0;
		if (lo <= L && R <= hi) return sum[ind];
		int M = (L+R)/2; 
		return qsum(lo,hi,2*ind,L,M)+qsum(lo,hi,2*ind+1,M+1,R);
	}
};