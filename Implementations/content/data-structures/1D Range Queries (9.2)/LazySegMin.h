/**
 * Description: Calculates min and # of mins
 * Source: Own
 * Verification: FHC19 Final D
 */

typedef pi T;
T operator+(const T& l, const T& r) {
	if (l.f != r.f) return min(l,r);
	return {l.f,l.s+r.s};
}

template<int SZ> struct LazySeg { 
	T sum[2*SZ];
	int lazy[2*SZ];
	LazySeg() {
		memset(sum,0,sizeof sum);
		memset(lazy,0,sizeof lazy);
	}
	void push(int ind, int L, int R) { // modify values for current node
		sum[ind].f += lazy[ind]; 
		if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind]; 
		lazy[ind] = 0; // pushed lazy to children
	}
	void pull(int ind) { // recalc values for current node
		sum[ind] = sum[2*ind]+sum[2*ind+1]; }
	void build() { 
		FOR(i,SZ,2*SZ) sum[i] = {0,1};
		ROF(i,1,SZ) pull(i); 
	}
	void upd(int lo, int hi, int inc, int ind = 1, int L = 0, int R = SZ-1) {
		push(ind,L,R);
		if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {
			lazy[ind] = inc; 
			push(ind,L,R); return;
		}
		int M = (L+R)/2;
		upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
		pull(ind);
	}
	T qsum(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
		push(ind,L,R);
		if (lo > R || L > hi) return {MOD,0};
		if (lo <= L && R <= hi) return sum[ind];
		int M = (L+R)/2;
		return qsum(lo,hi,2*ind,L,M)+qsum(lo,hi,2*ind+1,M+1,R);
	}
};