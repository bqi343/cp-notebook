/**
 * Description: 1D range minimum query
 * Source: KACTL
 * Verification: 
	* https://cses.fi/problemset/stats/1647/
	* http://wcipeg.com/problem/ioi1223
	* https://pastebin.com/ChpniVZL
 * Time: $O(N\log N)$ build, $O(1)$ query
 */

template<class T> struct RMQ {
	constexpr static int level(int x) { 
		return 31-__builtin_clz(x); 
	} // floor(log_2(x))
	vector<vi> jmp;
	vector<T> v;	
	int comb(int a, int b) { 
		return v[a] == v[b] ? min(a,b) : (v[a] < v[b] ? a : b); 
	} // index of minimum

	void init(const vector<T>& _v) {
		v = _v; jmp = {vi(sz(v))}; iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= sz(v); ++j) {
			jmp.pb(vi(sz(v)-(1<<j)+1));
			F0R(i,sz(jmp[j])) jmp[j][i] = comb(jmp[j-1][i],
									jmp[j-1][i+(1<<(j-1))]);
		}
	}
	
	int index(int l, int r) { // get index of min element
		int d = level(r-l+1);
		return comb(jmp[d][l],jmp[d][r-(1<<d)+1]);
	}
	T query(int l, int r) { return v[index(l,r)]; }
};