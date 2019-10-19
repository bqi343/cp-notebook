/**
 * Description: ?
 * Time: $O(N\alpha(N))$
 * Source: CSAcademy, KACTL
 * Verification: USACO superbull
 */

struct DSU {
	vi e;
	void init(int n) { e = vi(n,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } // path compression
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union-by-rank
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x;
		return 1;
	}
};