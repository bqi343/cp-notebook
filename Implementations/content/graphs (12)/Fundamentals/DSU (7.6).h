/**
 * Description: ?
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

// computes the minimum spanning tree in O(ElogE) time

template<class T> T kruskal(int n, vector<pair<T,pi>> edge) {
	sort(all(edge));
	T ans = 0; DSU D; D.init(n);
	trav(a,edge) if (D.unite(a.s.f,a.s.s)) ans += a.f; // edge is in MST
	return ans;
}
