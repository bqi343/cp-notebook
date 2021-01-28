#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; 
typedef string str; 

typedef pair<int,int> pi;
typedef pair<ll,ll> pl; 
typedef pair<ld,ld> pd; 

typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef vector<ld> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 

#define mp make_pair 
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() 
#define rsz resize
#define ins insert 
#define ft front() 
#define bk back()
#define pf push_front 
#define pb push_back
#define eb emplace_back 
#define lb lower_bound 
#define ub upper_bound 

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5; 
const ll INF = 1e18; 
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; 

template<class T> bool ckmin(T& a, const T& b) { 
	return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; }
int pct(int x) { return __builtin_popcount(x); } 

namespace input {
	template<class T> void re(complex<T>& x);
	template<class T1, class T2> void re(pair<T1,T2>& p);
	template<class T> void re(vector<T>& a);
	template<class T, size_t SZ> void re(array<T,SZ>& a);

	template<class T> void re(T& x) { cin >> x; }
	void re(double& x) { string t; re(t); x = stod(t); }
	void re(ld& x) { string t; re(t); x = stold(t); }
	template<class T, class... Ts> void re(T& t, Ts&... ts) { 
		re(t); re(ts...); 
	}

	template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = {a,b}; }
	template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
	template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
	template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
}

using namespace input;

namespace output {
	void pr(int x) { cout << x; }
	void pr(long x) { cout << x; }
	void pr(ll x) { cout << x; }
	void pr(unsigned x) { cout << x; }
	void pr(unsigned long x) { cout << x; }
	void pr(unsigned long long x) { cout << x; }
	void pr(float x) { cout << x; }
	void pr(double x) { cout << x; }
	void pr(ld x) { cout << x; }
	void pr(char x) { cout << x; }
	void pr(const char* x) { cout << x; }
	void pr(const string& x) { cout << x; }
	void pr(bool x) { pr(x ? "true" : "false"); }
	template<class T> void pr(const complex<T>& x) { cout << x; }
	
	template<class T1, class T2> void pr(const pair<T1,T2>& x);
	template<class T> void pr(const T& x);
	
	template<class T, class... Ts> void pr(const T& t, const Ts&... ts) { 
		pr(t); pr(ts...); 
	}
	template<class T1, class T2> void pr(const pair<T1,T2>& x) { 
		pr("{",x.f,", ",x.s,"}"); 
	}
	template<class T> void pr(const T& x) { 
		pr("{"); // const iterator needed for vector<bool>
		bool fst = 1; for (const auto& a: x) pr(!fst?", ":"",a), fst = 0; 
		pr("}");
	}
	
	void ps() { pr("\n"); } // print w/ spaces
	template<class T, class... Ts> void ps(const T& t, const Ts&... ts) { 
		pr(t); if (sizeof...(ts)) pr(" "); ps(ts...); 
	}
	
	void pc() { pr("]\n"); } // debug w/ commas
	template<class T, class... Ts> void pc(const T& t, const Ts&... ts) { 
		pr(t); if (sizeof...(ts)) pr(", "); pc(ts...); 
	}
	#define dbg(x...) pr("[",#x,"] = ["), pc(x);
}

using namespace output;

namespace io {
	void setIn(string s) { freopen(s.c_str(),"r",stdin); }
	void setOut(string s) { freopen(s.c_str(),"w",stdout); }
	void setIO(string s = "") {
		ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
		// cin.exceptions(cin.failbit); 
		// throws exception when do smth illegal
		// ex. try to read letter into int
		if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
	}
}

using namespace io;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

template<class T, int SZ> struct pseg {
	static const int LIM = 3e7;
	struct node { 
		int l,r; T val = 0,lazy = 0; 
		void inc(T x) { val += x, lazy += x; }
	};
	node d[LIM]; int nex = 0;
	//// HELPER
	int copy(int cur) { d[nex] = d[cur]; return nex++; }
	T comb(T a, T b) { return min(a,b); }
	void pull(int x){d[x].val=comb(d[d[x].l].val,d[d[x].r].val);} 
	void push(int cur, int L, int R) { 
		T& x = d[cur].lazy; if (!x) return;
		if (L != R) {
			d[d[cur].l = copy(d[cur].l)].inc(x);
			d[d[cur].r = copy(d[cur].r)].inc(x);
		}
		x = 0;
	}
	//// MAIN FUNCTIONS
	T query(int cur, int lo, int hi, int L, int R) {  
		if (lo <= L && R <= hi) return d[cur].val;
		if (R < lo || hi < L) return MOD;
		int M = (L+R)/2;
		return d[cur].lazy+comb(query(d[cur].l,lo,hi,L,M),
							query(d[cur].r,lo,hi,M+1,R));
	}
	int upd(int cur, int lo, int hi, T v, int L, int R) {
		if (R < lo || hi < L) return cur;
		int x = copy(cur);
		if (lo <= L && R <= hi) { d[x].inc(v); return x; }
		push(x,L,R); int M = (L+R)/2;
		d[x].l = upd(d[x].l,lo,hi,v,L,M);
		d[x].r = upd(d[x].r,lo,hi,v,M+1,R);
		pull(x); return x;
	}
	int build(const vector<T>& arr, int L, int R) {
		int cur = nex++;
		if (L == R) {
			if (L < sz(arr)) d[cur].val = arr[L];
			return cur;
		}
		int M = (L+R)/2;
		d[cur].l = build(arr,L,M), d[cur].r = build(arr,M+1,R);
		pull(cur); return cur;
	}
	//// PUBLIC
	vi loc;
	void upd(int lo, int hi, T v) { 
		loc.pb(upd(loc.bk,lo,hi,v,0,SZ-1)); }
	T query(int ti, int lo, int hi) { 
		return query(loc[ti],lo,hi,0,SZ-1); }
	void build(const vector<T>&arr) {loc.pb(build(arr,0,SZ-1));}
};

pseg<int,100000> p;

template<class T, int SZ> struct pseg2 {
	static const int LIMIT = 30000000; // adjust
	int l[LIMIT], r[LIMIT], nex = 0;
	T val[LIMIT], lazy[LIMIT];
	//// HELPER
	int copy(int cur) {
		int x = nex++;
		val[x]=val[cur],l[x]=l[cur],r[x]=r[cur],lazy[x]=lazy[cur];
		return x;
	}
	T comb(T a, T b) { return min(a,b); }
	void pull(int x) { val[x] = comb(val[l[x]],val[r[x]]); } 
	void push(int cur, int L, int R) { 
		if (!lazy[cur]) return;
		if (L != R) {
			l[cur] = copy(l[cur]);
			val[l[cur]] += lazy[cur], lazy[l[cur]] += lazy[cur];
			r[cur] = copy(r[cur]);
			val[r[cur]] += lazy[cur], lazy[r[cur]] += lazy[cur];
		}
		lazy[cur] = 0;
	}
	//// MAIN FUNCTIONS
	T query(int cur, int lo, int hi, int L, int R) {  
		if (lo <= L && R <= hi) return val[cur];
		if (R < lo || hi < L) return MOD;
		int M = (L+R)/2;
		return lazy[cur]+comb(query(l[cur],lo,hi,L,M),
							query(r[cur],lo,hi,M+1,R));
	}
	int upd(int cur, int lo, int hi, T v, int L, int R) {
		if (R < lo || hi < L) return cur;
		int x = copy(cur);
		if (lo <= L && R <= hi) { 
			val[x] += v, lazy[x] += v; 
			return x; 
		}
		push(x,L,R);
		int M = (L+R)/2;
		l[x] = upd(l[x],lo,hi,v,L,M);
		r[x] = upd(r[x],lo,hi,v,M+1,R);
		pull(x); return x;
	}
	int build(vector<T>& arr, int L, int R) {
		int cur = nex++;
		if (L == R) {
			if (L < sz(arr)) val[cur] = arr[L];
			return cur;
		}
		int M = (L+R)/2;
		l[cur] = build(arr,L,M), r[cur] = build(arr,M+1,R);
		pull(cur); return cur;
	}
	//// PUBLIC
	vi loc;
	void upd(int lo, int hi, T v) { 
		loc.pb(upd(loc.bk,lo,hi,v,0,SZ-1)); }
	T query(int ti, int lo, int hi) { 
		return query(loc[ti],lo,hi,0,SZ-1); }
	void build(vector<T>& arr) { loc.pb(build(arr,0,SZ-1)); }
};

pseg2<int,100000> p2;

/**
 * Description: Unused. A 32-bit pointer that points into BumpAllocator memory.
 * Source: Simon Lindholm
 * Status: tested
 */

/**
 * Description: When you need to dynamically allocate many objects and don't care about freeing them.
 	* "new X" otherwise has an overhead of something like 0.05us + 16 bytes per allocation.
 * Source: Simon Lindholm 
 * Status: tested
 */
/*
// Either globally or in a single class:
static char buf[450 << 20];
void* operator new(size_t s) {
	static size_t i = sizeof buf; assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) {}

template<class T> struct ptr {
	unsigned ind;
	ptr(T* p = 0) : ind(p ? unsigned((char*)p - buf) : 0) {
		assert(ind < sizeof buf); }
	T& operator*() const { return *(T*)(buf + ind); }
	T* operator->() const { return &**this; }
	T& operator[](int a) const { return (&**this)[a]; }
	explicit operator bool() const { return ind; }
};

template<class T, int SZ> struct pseg3 {
	static T comb(T a, T b) { return min(a,b); }
	struct node { 
		ptr<node> l,r;
		T val = 0, lazy = 0; 
		void inc(T x) { val += x, lazy += x; }
		void pull() { val = comb(l->val,r->val); }
	};
	typedef ptr<node> pn;
	pn copy(pn x) { return new node(*x); }
	//// HELPER
	void push(pn cur, int L, int R) { 
		T& x = cur->lazy; if (!x) return;
		if (L != R) {
			(cur->l = copy(cur->l))->inc(x);
			(cur->r = copy(cur->r))->inc(x);
		}
		x = 0;
	}
	//// MAIN FUNCTIONS
	T query(pn cur, int lo, int hi, int L, int R) {  
		if (lo <= L && R <= hi) return cur->val;
		if (R < lo || hi < L) return MOD;
		int M = (L+R)/2;
		return cur->lazy+comb(query(cur->l,lo,hi,L,M),
							query(cur->r,lo,hi,M+1,R));
	}
	pn upd(pn cur, int lo, int hi, T v, int L, int R) {
		if (R < lo || hi < L) return cur;
		auto x = copy(cur);
		if (lo <= L && R <= hi) { x->inc(v); return x; }
		push(x,L,R); int M = (L+R)/2;
		x->l = upd(x->l,lo,hi,v,L,M);
		x->r = upd(x->r,lo,hi,v,M+1,R);
		x->pull(); return x;
	}
	pn build(const vector<T>& arr, int L, int R) {
		pn cur = new node();
		if (L == R) {
			if (L < sz(arr)) cur->val = arr[L];
			return cur;
		}
		int M = (L+R)/2;
		cur->l = build(arr,L,M), cur->r = build(arr,M+1,R);
		cur->pull(); return cur;
	}
	//// PUBLIC
	vector<pn> loc;
	void upd(int lo, int hi, T v) { 
		loc.pb(upd(loc.bk,lo,hi,v,0,SZ-1)); }
	T query(int ti, int lo, int hi) { 
		return query(loc[ti],lo,hi,0,SZ-1); }
	void build(const vector<T>&arr) {loc.pb(build(arr,0,SZ-1));}
};

pseg3<int,100000> p3;*/


template<class T, int SZ> struct pseg {
	struct node { 
		int l,r; T val=0,lazy=0; 
		void inc(T x) { lazy += x; }
		T get() { return val+lazy; }
	};
	vector<node> d;
	int copy(int c) { d.pb(d[c]); return sz(d)-1; }
	T comb(T a, T b) { return min(a,b); }
	void pull(int c){d[c].val=comb(d[d[c].l].get(),d[d[c].r].get());} 
	//// MAIN FUNCTIONS
	T query(int c, int lo, int hi, int L, int R) {  
		if (lo <= L && R <= hi) return d[c].get();
		if (R < lo || hi < L) return MOD;
		int M = (L+R)/2;
		return d[c].lazy+comb(query(d[c].l,lo,hi,L,M),
							query(d[c].r,lo,hi,M+1,R));
	}
	int upd(int c, int lo, int hi, T v, int L, int R) {
		if (R < lo || hi < L) return c;
		int x = copy(c);
		if (lo <= L && R <= hi) { d[x].inc(v); return x; }
		int M = (L+R)/2;
		d[x].l = upd(d[x].l,lo,hi,v,L,M);
		d[x].r = upd(d[x].r,lo,hi,v,M+1,R);
		pull(x); return x;
	}
	int build(const vector<T>& arr, int L, int R) {
		int c = sz(d); d.eb();
		if (L == R) {
			if (L < sz(arr)) d[c].val = arr[L];
			return c;
		}
		int M = (L+R)/2;
		d[c].l = build(arr,L,M), d[c].r = build(arr,M+1,R);
		pull(c); return c;
	}
	vi loc; //// PUBLIC
	void upd(int lo, int hi, T v) { 
		loc.pb(upd(loc.bk,lo,hi,v,0,SZ-1)); }
	T query(int ti, int lo, int hi) { 
		return query(loc[ti],lo,hi,0,SZ-1); }
	void build(const vector<T>&arr) {loc.pb(build(arr,0,SZ-1));}
};

pseg4<int,100000> p4;

int n = 1e5;

int main() {
	// setIO();
	vi v(n); F0R(i,n) v[i] = rand()%1000+1;
	// ps("OK"); exit(0);
	vector<array<int,4>> upds;
	int num = 1;
	F0R(i,5e5) {
		int lo = rand()%n, hi = rand()%n, inc = rand()%100+1;
		if (lo > hi) swap(lo,hi);
		int q = rand()%2;
		if (q == 0) {
			upds.pb({-1,lo,hi,inc});
			num ++;
		} else {
			upds.pb({rand()%num,lo,hi,inc});
		}
	}
	/*// ps("OK"); exit(0);
	clock_t beg = clock();
	ll sum0 = 0;
	p.build(v); 
	each(t,upds) {
		if (t[0] < 0) {
			p.upd(t[1],t[2],t[3]);
		} else {
			assert(t[0] < sz(p.loc));
			sum0 += p.query(t[0],t[1],t[2]);
		}
	}
	ps(sum0,p.nex,(db)(clock()-beg)/CLOCKS_PER_SEC);
	// exit(0);
	beg = clock();
	ll sum1 = 0;
	p2.build(v);
	each(t,upds) {
		if (t[0] < 0) {
			p2.upd(t[1],t[2],t[3]);
		} else {
			sum1 += p2.query(t[0],t[1],t[2]);
		}
	}
	ps(sum1,p2.nex,(db)(clock()-beg)/CLOCKS_PER_SEC);
	{
		beg = clock();
		ll sum3 = 0;
		// ps(sum3,(db)(clock()-beg)/CLOCKS_PER_SEC);
		p3.build(v);
		each(t,upds) {
			if (t[0] < 0) {
				p3.upd(t[1],t[2],t[3]);
			} else {
				sum3 += p3.query(t[0],t[1],t[2]);
			}
		}
		ps(sum3,(db)(clock()-beg)/CLOCKS_PER_SEC);
	}*/
	// 198696657428
	{
		clock_t beg = clock();
		ll sum4 = 0;
		// ps(sum3,(db)(clock()-beg)/CLOCKS_PER_SEC);
		p4.build(v);
		each(t,upds) {
			if (t[0] < 0) {
				p4.upd(t[1],t[2],t[3]);
			} else {
				sum4 += p4.query(t[0],t[1],t[2]);
			}
		}
		ps("HA");
		ps(sum4,sz(p4.d),(db)(clock()-beg)/CLOCKS_PER_SEC);
	}
	// you should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
*/
