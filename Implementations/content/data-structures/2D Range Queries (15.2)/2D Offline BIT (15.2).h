/**
 * Description: similar to merge-sort tree, but offline updates
	* O(nlogn) memory, O(nlog^2n) time with better constant
 * Source: own
 * Verification: https://dmoj.ca/problem/occ19g4
 */

 template<class T, int SZ> struct BIT2D { 
	bool mode = 0; // mode = 1 -> initialized
	vpi todo;
	int cnt[SZ], st[SZ];
	vi val, bit;
	
	void init() {
		assert(!mode); mode = 1;
		int lst[SZ]; F0R(i,SZ) lst[i] = cnt[i] = 0;
		sort(all(todo),[](const pi& a, const pi& b) { return a.s < b.s; });
		trav(t,todo) for (int X = t.f; X < SZ; X += X&-X) 
			if (lst[X] != t.s) {
				lst[X] = t.s;
				cnt[X] ++;
			}
		int sum = 0;
		F0R(i,SZ) {
			st[i] = sum; lst[i] = 0; // stores start index for each x
			sum += cnt[i];
		}
		val.rsz(sum); bit.rsz(sum); // store all BITs in single vector
		trav(t,todo) for (int X = t.f; X < SZ; X += X&-X) 
			if (lst[X] != t.s) {
				lst[X] = t.s; 
				val[st[X]++] = t.s;
			}
	}
	
	int rank(int y, int l, int r) {
		return ub(begin(val)+l,begin(val)+r,y)-begin(val)-l;
	}
	
	void UPD(int x, int y, int t) {
		int z = st[x]-cnt[x]; // BIT covers range from z to st[x]-1
		for (y = rank(y,z,st[x]); y <= cnt[x]; y += y&-y) 
			bit[z+y-1] += t;
	}
	void upd(int x, int y, int t = 1) { // x-coordinate in [1,SZ)
		if (!mode) todo.pb({x,y});
		else {
			for (; x < SZ; x += x&-x) UPD(x,y,t);
		}
	}
	
	int QUERY(int x, int y) {
		int z = st[x]-cnt[x], ans = 0;
		for (y = rank(y,z,st[x]); y; y -= y&-y) 
			ans += bit[z+y-1];
		return ans;
	}
	int query(int x, int y) { 
		assert(mode);
		int t = 0; for (; x; x -= x&-x) t += QUERY(x,y);
		return t;
	}
	int query(int lox, int hix, int loy, int hiy) { // query number of elements within a rectangle
		return query(hix,hiy)-query(lox-1,hiy)
			-query(hix,loy-1)+query(lox-1,loy-1);
	}
};