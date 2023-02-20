/**
 * Description: Faster 1D range minimum query. 
 * Source: KACTL
 * Verification: 
	* https://judge.yosupo.jp/submission/126814
 * Memory: O(N\log N)
 * Time: O(1)
 */

tcT, size_t SZ> struct RMQ { // floor(log_2(x))
	static constexpr int level(int x) { return 31-__builtin_clz(x); }
	array<array<T,SZ>, level(SZ)+1> jmp;
	T cmb(T a, T b) { return min(a, b); }
	void init(const V<T>& v) { assert(sz(v) <= SZ);
		copy(all(v), begin(jmp[0]));
		for (int j = 1; 1<<j <= sz(v); ++j) {
			F0R(i,sz(v)-(1<<j)+1) jmp[j][i] = cmb(jmp[j-1][i],
				jmp[j-1][i+(1<<(j-1))]);
		}
	}
	T query(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return cmb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
};