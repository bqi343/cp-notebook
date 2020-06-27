/**
 * Description: LiChao Segment Tree
 * Source: atatomir, misc
 * Verification: CSA Squared Ends
   * https://judge.yosupo.jp/problem/segment_add_get_min
 */

struct Line {
	int k; ll m;
	Line(int _k, ll _m) { k = _k, m = _m; }
	Line() : Line(0,LLONG_MIN) { }
	ll get(ll x) { return k*x+m; }
	bool majorize(Line X, ll L, ll R) { 
		return get(L) >= X.get(L) && get(R) >= X.get(R); }
};

struct lc {
	lc* c[2]; Line S;
	lc() { c[0] = c[1] = NULL; S = Line(); }
	~lc() { F0R(i,2) delete c[i]; }
	void mc(int i) { if (!c[i]) c[i] = new lc(); }
	ll mid(ll x) { return x&1?(x-1)/2:x/2; }
	ll query(ll X, ll L, ll R) {
		ll ans = S.get(X), M = mid(L+R);
		if (X <= M) {
			if (c[0]) ckmax(ans,c[0]->query(X,L,M));
		} else {
			if (c[1]) ckmax(ans,c[1]->query(X,M+1,R));
		}
		return ans;
	}
	void modify(Line X, ll L, ll R) {
		if (X.majorize(S,L,R)) swap(X,S);
		if (S.majorize(X,L,R)) return;
		if (S.get(L) < X.get(L)) swap(X,S);
		ll M = mid(L+R);
		if (X.get(M) >= S.get(M)) swap(X,S), mc(0), c[0]->modify(X,L,M);
		else mc(1), c[1]->modify(X,M+1,R);
	}
	void upd(Line X, ll lo, ll hi, ll L, ll R) {
		if (R < lo || hi < L) return;
		if (lo <= L && R <= hi) return modify(X,L,R);
		ll M = mid(L+R);
		if (lo <= M) mc(0), c[0]->upd(X,lo,hi,L,M);
		if (hi > M) mc(1), c[1]->upd(X,lo,hi,M+1,R);
	}
};
