/**
 * Description: bitset of variable size
 * Source: Own
 	* Also see https://www.hackerrank.com/contests/noi-ph-2019-finals-1/challenges/sumbong-centers/editorial
 	* Order of operations
 		* https://en.cppreference.com/w/cpp/language/operator_precedence
 * Verification: see bset.cpp
 */

struct bset {
	typedef uint64_t ul;
	int size; vector<ul> b; 
	bset(int x) : size(x), b((x+63)/64) {}
	bool get(int x) const { return (b[x/64]>>(x%64))&1; }
	void flip(int x) { b[x/64] ^= (ul)1<<(x%64); }
	void set(int x) { if (!get(x)) flip(x); }
	int count() {
		int res = 0; each(t,b) res += __builtin_popcountll(t);
		return res; }
	friend void pr(const bset&x){F0R(i,x.size)pr((int)x.get(i));}
	bset& operator|=(const bset& r) {
		assert(size == r.size); F0R(i,sz(b)) b[i] |= r.b[i]; 
		return b; }
	bset& operator&=(const bset& r) {
		assert(size == r.size); F0R(i,sz(b)) b[i] &= r.b[i]; 
		return b; }
	bset& operator^=(const bset& r) {
		assert(size == r.size); F0R(i,sz(b)) b[i] ^= r.b[i]; 
		return b; }
	bset shift(int inc) { // cyclic shift b to right
		inc %= size; if (inc < 0) inc += size;
		bset res(size);
		int r0 = inc/64, r1 = inc%64;
		int l0 = (size-inc)/64, l1 = (size-inc)%64;
		F0R(i,sz(b)-r0) {
			res.b[i+r0] |= b[i]<<r1;
			if (r1 && i+r0+1 < sz(b)) 
				res.b[i+r0+1] |= b[i]>>(64-r1);
		}
		FOR(i,l0,sz(b)) {
			res.b[i-l0] |= b[i]>>l1;
			if (l1 && i >= l0+1) 
				res.b[i-l0-1] |= b[i]<<(64-l1);
		}
		int rem = size%64; if (rem) res.b.bk &= ((ul)1<<rem)-1;
		return res;
	}
	int findNext(int x) { // first bit after x
		int i = x < 0 ? -1 : x/64, p = (x+1)%64;
		if (p != 0) {
			ul a = b[i]; a ^= a&(((ul)1<<p)-1);
			int t = __builtin_ffsll(a);
			if (t) return 64*i+t-1;
		}
		while (++i < sz(b)) {
			int t = __builtin_ffsll(b[i]);
			if (t) return 64*i+t-1;
		}
		return size;
	}
};
