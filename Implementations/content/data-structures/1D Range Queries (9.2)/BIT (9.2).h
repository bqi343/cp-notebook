/**
 * Description: $N$-D range sum query with point update
 * Source: https://codeforces.com/blog/entry/64914
 * Verification: SPOJ matsum
 * Time: O((\log N)^D)
 */

template <class T, int ...Ns> struct BIT {
	T val = 0;
	void upd(T v) { val += v; }
	T query() { return val; }
};

template <class T, int N, int... Ns> struct BIT<T, N, Ns...> {
	BIT<T,Ns...> bit[N+1];
	template<typename... Args> void upd(int pos, Args... args) {
		for (; pos <= N; pos += (pos&-pos)) bit[pos].upd(args...);
	}
	template<typename... Args> T sum(int r, Args... args) {
		T res = 0; for (; r; r -= (r&-r)) res += bit[r].query(args...); 
		return res;
	}
	template<typename... Args> T query(int l, int r, Args... args) {
		return sum(r,args...)-sum(l-1,args...);
	}
}; // BIT<int,10,10> gives a 2D BIT