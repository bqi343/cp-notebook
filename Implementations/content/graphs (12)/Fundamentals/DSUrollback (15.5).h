/**
 * Description: Disjoint Set Union with Rollback
 * Source: see DSU
 * Verification: https://codeforces.com/contest/1140/problem/F
 */

template<int SZ> struct DSU {
	int par[SZ], sz[SZ];
	vpi stor;

	DSU() {
		F0R(i,SZ) par[i] = i, sz[i] = 1;
	}

	int get(int x) { // no path compression
		if (x == par[x]) return x;
		return get(par[x]);
	}

	void unite(int x, int y) { // union-by-rank
		x = get(x), y = get(y);
		if (x == y) { stor.pb({-1,-1}); return; }
		if (sz[x] < sz[y]) swap(x,y);
		stor.pb({x,y}); sz[x] += sz[y], par[y] = x;
	}

	void rollback() { // delete last edge added
		auto a = stor.back(); stor.pop_back();
		int x = a.f, y = a.s;
		if (x == -1) return;
		sz[x] -= sz[y]; par[y] = y;
	}
};

DSU<MX> D;

template<int SZ> struct Seg { // answer dynamic connectivity queries offline
	vpi seg[2*SZ];

	void upd(int l, int r, pi p) {	// add edge p to all times in interval [l, r]
		r++;
		for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
			if (l&1) seg[l++].pb(p);
			if (r&1) seg[--r].pb(p);
		}
	}

	void process(int ind) {
		trav(t,seg[ind]) D.unite(t.f,t.s);
		if (ind >= SZ) {
			// do stuff with D at time ind-SZ
		} else process(2*ind), process(2*ind+1);
		trav(t,seg[ind]) D.rollback();
	}
};
