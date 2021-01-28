/**
 * Description: Area of rectangle union using segment tree that 
	* keeps track of min and # of mins. Rectangles are in form {{x1,x2},{y1,y2}}.
 * Source: Own
 * Verification: FHC19 Final D
	* https://cses.fi/problemset/task/1741/
 */

typedef pi T;
T operator+(const T& l, const T& r) {
	return l.f != r.f ? min(l,r) : T{l.f,l.s+r.s}; }

const int SZ = 1<<18;
struct LazySeg { 
	const T ID = {MOD,0}; T comb(T a, T b) { return a+b; }
	T seg[2*SZ]; int lazy[2*SZ]; 
	LazySeg() { F0R(i,2*SZ) seg[i] = {0,0}, lazy[i] = 0; }
	void push(int ind, int L, int R) { /// modify values for current node
		if (L != R) F0R(i,2) lazy[2*ind+i] += lazy[ind]; /// prop to children
		seg[ind].f += lazy[ind]; // dependent on operation
		lazy[ind] = 0; 
	} // recalc values for current node
	void pull(int ind) { seg[ind] = comb(seg[2*ind],seg[2*ind+1]); }
	void build() { ROF(i,1,SZ) pull(i); }
	void upd(int lo,int hi,int inc,int ind=1,int L=0, int R=SZ-1) {
		push(ind,L,R); if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) { 
			lazy[ind] = inc; push(ind,L,R); return; }
		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M); 
		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);
	}
};
 
ll area(vector<pair<pi,pi>> v) {
	LazySeg L;
	vi y; each(t,v) y.pb(t.s.f), y.pb(t.s.s);
	sort(all(y)); y.erase(unique(all(y)),y.end());
	F0R(i,sz(y)-1) L.seg[SZ+i].s = y[i+1]-y[i];
	L.build();
	vector<array<int,4>> ev; // sweep line
	each(t,v) {
		t.s.f = lb(all(y),t.s.f)-begin(y);
		t.s.s = lb(all(y),t.s.s)-begin(y)-1;
		ev.pb({t.f.f,1,t.s.f,t.s.s});
		ev.pb({t.f.s,-1,t.s.f,t.s.s});
	}
	sort(all(ev));
	ll ans = 0;
	F0R(i,sz(ev)-1) {
		const auto& t = ev[i]; L.upd(t[2],t[3],t[1]);
		int len = y.bk-y.ft-L.seg[1].s; // L.mn[0].f should equal 0
		ans += (ll)(ev[i+1][0]-t[0])*len;
	}
	return ans;
}
