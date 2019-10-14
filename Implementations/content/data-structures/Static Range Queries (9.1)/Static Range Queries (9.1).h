/**
 * Description: constructs in O(nlogn) and queries a range in O(1)
 * Source: own
 * Verification: https://www.codechef.com/problems/SEGPROD
 */ 
 
template<class T, int SZ> struct RangeQuery {
	int n;
	T stor[SZ][32-__builtin_clz(SZ)], id = 1;
	vector<T> a;
	
	T comb (T a, T b) { return mul(a,b); } // associative operation
	
	void fill(int l, int r, int ind) {
		if (ind < 0) return;
		int m = (l+r)/2;
		T prod = id; FORd(i,l,m) stor[i][ind] = prod = comb(a[i],prod);
		prod = id; FOR(i,m,r) stor[i][ind] = prod = comb(prod,a[i]);
		fill(l,m,ind-1); fill(m,r,ind-1);
	}
	
	void init() {
		n = 1; while ((1<<n) < sz(a)) n ++;
		a.resz(1<<n); fill(0,(1<<n),n-1);
	}
	
	T query(int l, int r) {
		if (l == r) return a[l];
		int t = 31-__builtin_clz(r^l);
		return comb(stor[l][t],stor[r][t]);
	}
};