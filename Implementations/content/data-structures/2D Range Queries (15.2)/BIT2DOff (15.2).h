/**
 * Description: point update and rectangle sum with offline 2D BIT. 
	* For each of the points to be updated, $x\in (0,SZ)$ and $y\neq 0$.
 * Time: O(N\log^2 N)
 * Memory: O(N\log N)
 * Source: Own
 * Verification: 
 	* https://dmoj.ca/problem/occ19g4
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=722 (753 ms)
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=601 (679 ms)
 */

template<class T, int SZ> struct OffBIT2D { 
	bool mode = 0; // mode = 1 -> initialized
	vpi todo; // locations of updates to process
	int cnt[SZ], st[SZ];
	vi val; vector<T> bit; // store all BITs in single vector
	void init() { assert(!mode); mode = 1;
		int lst[SZ]; F0R(i,SZ) lst[i] = cnt[i] = 0;
		sort(all(todo),[](const pi& a, const pi& b) { 
			return a.s < b.s; });
		each(t,todo) for (int x = t.f; x < SZ; x += x&-x) 
			if (lst[x] != t.s) lst[x] = t.s, cnt[x] ++;
		int sum = 0; F0R(i,SZ) lst[i] = 0, st[i] = (sum += cnt[i]);
		val.rsz(sum); bit.rsz(sum); reverse(all(todo));
		each(t,todo) for (int x = t.f; x < SZ; x += x&-x) 
			if (lst[x] != t.s) lst[x] = t.s, val[--st[x]] = t.s;
	}
	int rank(int y, int l, int r) {
		return ub(begin(val)+l,begin(val)+r,y)-begin(val)-l; }
	void UPD(int x, int y, T t) {
		for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y) 
			bit[st[x]+y-1] += t; }
	void upd(int x, int y, T t) { 
		if (!mode) todo.pb({x,y});
		else for (;x<SZ;x+=x&-x) UPD(x,y,t); }
	int QUERY(int x, int y) { T res = 0;
		for (y = rank(y,st[x],st[x]+cnt[x]); y; y -= y&-y) res += bit[st[x]+y-1];
		return res; }
	T query(int x, int y) { assert(mode);
		T res = 0; for (;x;x-=x&-x) res += QUERY(x,y);
		return res; }
	T query(int xl, int xr, int yl, int yr) { 
		return query(xr,yr)-query(xl-1,yr)
			-query(xr,yl-1)+query(xl-1,yl-1); }
};
