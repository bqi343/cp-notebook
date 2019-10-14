/**
 * Description: calculates area of union of rectangles in the form [x1,x2) x [y1,y2)
 * Source: Own
 * Verification: 
	* https://cses.fi/problemset/task/1741/
	* https://codeforces.com/problemset/problem/494/E
 */

pi operator+(const pi& l, const pi& r) {
	if (l.f != r.f) return min(l,r);
	return {l.f,l.s+r.s};
}

const int SZ = 1<<18;

template<class T> struct LazySegTree { // stores min + # of mins
	T lazy[2*SZ]; // set SZ to a power of 2
	pair<T,int> mn[2*SZ];
	LazySegTree() {
		memset(lazy,0,sizeof lazy);
		F0R(i,2*SZ) mn[i] = {0,0};
	}
	
	void push(int ind, int L, int R) {
		mn[ind].f += lazy[ind];
		if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
		lazy[ind] = 0;
	}
	
	void pull(int ind) { mn[ind] = mn[2*ind]+mn[2*ind+1]; }
	void build() { ROF(i,1,SZ) pull(i); }
	
	void upd(int lo, int hi, ll inc, int ind = 1, int L = 0, int R = SZ-1) {
		push(ind,L,R);
		if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {
			lazy[ind] = inc;
			push(ind,L,R);
			return;
		}
		
		int M = (L+R)/2;
		upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
		pull(ind);
	}
};

ll area(vector<pair<pi,pi>> v) { // area of union of rectangles
	LazySegTree<int> L;
	vi y; trav(t,v) y.pb(t.s.f), y.pb(t.s.s);
	sort(all(y)); y.erase(unique(all(y)),y.end());
	F0R(i,sz(y)-1) L.mn[SZ+i].s = y[i+1]-y[i]; // compress coordinates
	L.build();

	vector<array<int,4>> ev; // sweep line
	trav(t,v) {
		t.s.f = lb(all(y),t.s.f)-begin(y);
		t.s.s = lb(all(y),t.s.s)-begin(y)-1;
		ev.pb({t.f.f,1,t.s.f,t.s.s});
		ev.pb({t.f.s,-1,t.s.f,t.s.s});
	}
	sort(all(ev));

	ll ans = 0;
	F0R(i,sz(ev)-1) {
		const auto& t = ev[i];
		L.upd(t[2],t[3],t[1]);
		int len = y.back()-y.front()-L.mn[1].s; // L.mn[0].f should equal 0
		ans += (ll)(ev[i+1][0]-t[0])*len;
	}
	return ans;
}