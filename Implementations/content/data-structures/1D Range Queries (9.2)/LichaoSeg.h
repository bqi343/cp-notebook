/**
 * Description: LiChao Segment Tree
 * Source: atatomir, misc
 * Verification: CSA Squared Ends
 */

struct Line {
	ll k,m;
	Line(ll _k, ll _m) { k = _k, m = _m; }
	Line() : Line(0,-INF) { }
	ll get(ll x) { return k*x+m; }
	bool majorize(Line X, ll L, ll R) { 
		return get(L) >= X.get(L) && get(R) >= X.get(R); 
	}
};

struct lc {
	lc* c[2];
	Line S;
	
	lc() {
		c[0] = c[1] = NULL;
		S = Line();
	}
	
	void rm() {
		if (c[0]) c[0]->rm();
		if (c[1]) c[1]->rm();
		delete this;
	}
	
	void mc(int i) {
		if (!c[i]) c[i] = new lc();
	}
	
	ll query(ll X, ll L, ll R) {
		ll ans = S.get(X), M = (L+R)/2;
		if (X <= M) return max(ans, c[0] ? c[0]->query(X,L,M): -INF);
		return max(ans, c[1] ? c[1]->query(X,M+1,R): -INF);
	}
	
	void modify(Line X, ll L, ll R) {
		if (X.majorize(S,L,R)) swap(X,S);
		if (S.majorize(X,L,R)) return;
		if (S.get(L) < X.get(L)) swap(X,S);
		
		ll M = (L+R)/2;
		if (X.get(M) >= S.get(M)) swap(X,S), mc(0), c[0]->modify(X,L,M);
		else mc(1), c[1]->modify(X,M+1,R);
	}
	
	void upd(Line X, ll lo, ll hi, ll L, ll R) { // untested
		if (R < hi || L < lo) return;
		if (lo <= L && R <= hi) { modify(X,L,R); return; }
		ll M = (L+R)/2;
		mc(0), c[0]->upd(X,lo,hi,L,M);
		mc(1), c[1]->upd(X,lo,hi,M+1,R);
	}
};
