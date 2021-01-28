#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld; 
typedef double db; 
typedef string str; 

typedef pair<int, int> pi;
typedef pair<ll,ll> pl; 
typedef pair<ld,ld> pd; 

typedef vector<int> vi; 
typedef vector<ll> vl;
typedef vector<ld> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define each(a,x) for (auto& a: x)

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x) 
#define rsz resize
#define ins insert 

#define mp make_pair
#define pb push_back
#define eb emplace_back 
#define f first
#define s second
#define lb lower_bound 
#define ub upper_bound 

const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int MX = 2e5+5;
const ll INF = 1e18; 
const ld PI = 4*atan((ld)1); 

template<class T> bool ckmin(T& a, const T& b) { 
	return a > b ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; }

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

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

	template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = cd(a,b); }
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
		cin.sync_with_stdio(0); cin.tie(0); // fast I/O
		// cin.exceptions(cin.failbit); // ex. throws exception when you try to read letter into int
		if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
	}
}

using namespace io;

template<class T> struct modular {
	T val; 
	explicit operator T() const { return val; }
	modular() { val = 0; }
	modular(const ll& v) { 
		val = (-MOD <= v && v <= MOD) ? v : v % MOD;
		if (val < 0) val += MOD;
	}
	// friend ostream& operator<<(ostream& os, const modular& a) { return os << a.val; }
	friend void pr(const modular& a) { pr(a.val); }
	friend void re(modular& a) { ll x; re(x); a = modular(x); }
   
	friend bool operator==(const modular& a, const modular& b) { 
		return a.val == b.val; }
	friend bool operator!=(const modular& a, const modular& b) { 
		return !(a == b); }
	friend bool operator<(const modular& a, const modular& b) { 
		return a.val < b.val; }

	modular operator-() const { return modular(-val); }
	modular& operator+=(const modular& m) { 
		if ((val += m.val) >= MOD) val -= MOD; 
		return *this; }
	modular& operator-=(const modular& m) { 
		if ((val -= m.val) < 0) val += MOD; 
		return *this; }
	modular& operator*=(const modular& m) { 
		val = (ll)val*m.val%MOD; return *this; }
	friend modular pow(modular a, ll p) {
		modular ans = 1; 
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans;
	}
	friend modular inv(const modular& a) { 
		assert(a != 0); return pow(a,MOD-2); 
	}
	modular& operator/=(const modular& m) { 
		return (*this) *= inv(m); }
	
	friend modular operator+(modular a, const modular& b) { 
		return a += b; }
	friend modular operator-(modular a, const modular& b) { 
		return a -= b; }
	friend modular operator*(modular a, const modular& b) { 
		return a *= b; }
	
	friend modular operator/(modular a, const modular& b) { 
		return a /= b; }
};

typedef modular<int> mi;
typedef pair<mi,mi> pmi;
typedef vector<mi> vmi;
typedef vector<pmi> vpmi;

typedef ll T;
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }

namespace Point {
	typedef pair<T,T> P;
	typedef vector<P> vP;

	T norm(P x) { return x.f*x.f+x.s*x.s; }
	T abs(P x) { return sqrt(norm(x)); }
	T angle(P x) { return atan2(x.s,x.f); }
	P conj(P x) { return P(x.f,-x.s); }
	P perp(P x) { return P(-x.s,x.f); }
	P dir(T ang) {
		auto c = exp(ang*complex<T>(0,1));
		return P(c.real(),c.imag());
	}
	
	P operator+(const P& l, const P& r) { 
		return P(l.f+r.f,l.s+r.s); }
	P operator-(const P& l, const P& r) { 
		return P(l.f-r.f,l.s-r.s); }
	P operator*(const P& l, const T& r) { 
		return P(l.f*r,l.s*r); }
	P operator*(const T& l, const P& r) { return r*l; }
	P operator/(const P& l, const T& r) { 
		return P(l.f/r,l.s/r); }
	P operator*(const P& l, const P& r) { 
		return P(l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s); }
	P operator/(const P& l, const P& r) { 
		return l*conj(r)/norm(r); }
	P& operator+=(P& l, const P& r) { return l = l+r; }
	P& operator-=(P& l, const P& r) { return l = l-r; }
	P& operator*=(P& l, const T& r) { return l = l*r; }
	P& operator/=(P& l, const T& r) { return l = l/r; }
	P& operator*=(P& l, const P& r) { return l = l*r; }
	P& operator/=(P& l, const P& r) { return l = l/r; }
	
	P unit(P x) { return x/abs(x); }
	T dot(P a, P b) { return (conj(a)*b).f; }
	T cross(P a, P b) { return (conj(a)*b).s; }
	T cross(P p, P a, P b) { return cross(a-p,b-p); }
	P rotate(P a, T b) { return a*P(cos(b),sin(b)); }
	P reflect(P p, P a, P b) { 
		return a+conj((p-a)/(b-a))*(b-a); }
	P foot(P p, P a, P b) { return (p+reflect(p,a,b))/(T)2; }
	bool onSeg(P p, P a, P b) { 
		return cross(a,b,p) == 0 && dot(p-a,p-b) <= 0; }
};
using namespace Point;

pair<vi,vi> ulHull(const vP& P) {
	vi p(sz(P)), u, l; iota(all(p), 0);
	sort(all(p), [&P](int a, int b) { return P[a] < P[b]; });
	each(i,p) {
		#define ADDP(C, cmp) while (sz(C) > 1 && cross(\
			P[C[sz(C)-2]],P[C.back()],P[i]) cmp 0) C.pop_back(); C.pb(i);
		ADDP(u, >=); ADDP(l, <=);
	}
	return {u,l};
}
vi hullInd(const vP& P) {
	vi u,l; tie(u,l) = ulHull(P);
	if (sz(l) <= 1) return l;
	if (P[l[0]] == P[l[1]]) return {0};
	l.insert(end(l),u.rbegin()+1,u.rend()-1); return l;
}
vP hull(const vP& P) {
	vi v = hullInd(P);
	vP res; each(t,v) res.pb(P[t]);
	return res;
}

int UP = 50;
P gen() {
	return P(rand()%UP,rand()%UP);
}


typedef array<P, 2> Line;
#define cmp(i,j) sgn(cross(perp(dir),poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1,i) >= 0 && cmp(i,i-1+n) < 0
int extrVertex(const vP& poly, P dir) {
	int n = sz(poly), lo = 0, hi = n;
	if (extr(0)) return 0;
	while (lo+1 < hi) {
		int m = (lo+hi) / 2;
		if (extr(m)) return m;
		int ls = cmp(lo + 1, lo), ms = cmp(m+1,m);
		(ls < ms || (ls == ms && ls == cmp(lo,m)) ? hi : lo) = m;
	}
	return lo;
}
vi same(Line line, const vP& poly, int a) { // points on same parallel as a
	int n = sz(poly); P dir = perp(line[0]-line[1]); 
	if (cmp(a+n-1,a) == 0) return {(a+n-1)%n,a};
	if (cmp(a,a+1) == 0) return {a,(a+1)%n};
	return {a};
}
#define cmpL(i) sgn(cross(line[0],line[1],poly[i]))
pair<int,vi> lineHull(Line line, const vP& poly) {
	int n = sz(poly); assert(n>1);
	int endA = extrVertex(poly,perp(line[0]-line[1])); // lowest
	if (cmpL(endA) >= 0) return {1,same(line,poly,endA)};
	int endB = extrVertex(poly,perp(line[1]-line[0])); // highest
	if (cmpL(endB) <= 0) return {-1,same(line,poly,endB)}; 
	array<int,2> res;
	F0R(i,2) {
		int lo = endA, hi = endB; if (hi < lo) hi += n;
		while (lo < hi) {
			int m = (lo+hi+1)/2;
			if (cmpL(m%n) == cmpL(endA)) lo = m;
			else hi = m-1;
		}
		res[i] = lo%n; swap(endA,endB);
	}
	if (cmpL((res[0]+1)%n) == 0) res[0] = (res[0]+1)%n;
	return {0,{(res[1]+1)%n,res[0]}};
}

vi generate(Line line, vP& poly, pair<int,vi> p) {
	int n = sz(poly);
	int x = p.s[0]; assert(0 <= x && x < n);
	if (p.f > 0 && cmpL(x) > 0) return {};
	if (p.f < 0 && cmpL(x) < 0) return {};
	vi v;
	if (sz(p.s) > 1) {
		while (x != p.s[1]) {
			v.pb(x);
			x = (x+1)%n;
		}
	}
	v.pb(x);
	sort(all(v)); return v;
}

vi naive(Line line, vP& poly) {
	int n = sz(poly);
	bool pos = 0, neg = 0;
	F0R(i,n) {
		int x = cmpL(i);
		if (x > 0) pos = 1;
		if (x < 0) neg = 1;
	}
	vi v;
	if (!pos || !neg) {
		F0R(i,n) {
			int x = cmpL(i);
			if (x == 0) v.pb(i);
		}
	} else {
		F0R(i,n) {
			int x = cmpL(i);
			if (x <= 0) v.pb(i);
		}
	}
	return v;
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	vP a = {{5,-5},{4,0},{-3,0}};
	P x = {0,0}, y = {1,0};
	int correct = 0;
	F0R(i,10000) {
		vP v; F0R(j,20) v.pb(gen());
		v = hull(v); if (sz(v) <= 2) continue;
		F0R(j,100) {
			P a = gen(), b = gen(); if (a == b) continue;
			auto x = generate({a,b},v,lineHull({a,b},v));
			auto y = naive({a,b},v);
			if (x != y) {
				ps("??",v,i,j);
				ps(a,b);
				ps(x);
				ps(y);
				exit(0);
			}
			correct ++;
		}
	}
	ps(correct);
	// you should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?), slow multiset operations
	* do smth instead of nothing and stay organized
*/
