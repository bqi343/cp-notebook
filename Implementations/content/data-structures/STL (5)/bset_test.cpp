#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; 
typedef string str; 

typedef pair<int,int> pi;
typedef pair<ll,ll> pl; 
typedef pair<ld,ld> pd; 
#define mp make_pair
#define f first
#define s second

typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef vector<ld> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 

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

const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int MX = 2e5+5;
const ll INF = 1e18; 
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; 

template<class T> bool ckmin(T& a, const T& b) { 
	return a > b ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; }
int pc(int x) { return __builtin_popcount(x); } 

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, 
	rb_tree_tag, tree_order_statistics_node_update>; 
// change null_type for map
#define ook order_of_key
#define fbo find_by_order

void treeExample() {
	Tree<int> t, t2; t.insert(8);
	auto it = t.insert(10).f; assert(it == t.lb(9));
	assert(t.ook(10) == 1); assert(t.ook(11) == 2);
	assert(*t.fbo(0) == 8);
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}

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
		ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
		// cin.exceptions(cin.failbit); 
		// throws exception when do smth illegal
		// ex. try to read letter into int
		if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
	}
}

using namespace io;

struct mi {
	typedef decay<decltype(MOD)>::type T; 
 	/// don't silently convert to T
	T v; explicit operator T() const { return v; }
	mi() { v = 0; }
	mi(ll _v) { 
		v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
		if (v < 0) v += MOD;
	}
	friend bool operator==(const mi& a, const mi& b) { 
		return a.v == b.v; }
	friend bool operator!=(const mi& a, const mi& b) { 
		return !(a == b); }
	friend bool operator<(const mi& a, const mi& b) { 
		return a.v < b.v; }
	friend void re(mi& a) { ll x; re(x); a = mi(x); }
	friend void pr(const mi& a) { pr(a.v); }
	friend ostream& operator<<(ostream& os, const mi& a) { 
		return os << a.v; }
   
	mi& operator+=(const mi& m) { 
		if ((v += m.v) >= MOD) v -= MOD; 
		return *this; }
	mi& operator-=(const mi& m) { 
		if ((v -= m.v) < 0) v += MOD; 
		return *this; }
	mi& operator*=(const mi& m) { 
		v = (ll)v*m.v%MOD; return *this; }
	mi& operator/=(const mi& m) { return (*this) *= inv(m); }
	friend mi pow(mi a, ll p) {
		mi ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans;
	}
	friend mi inv(const mi& a) { assert(a.v != 0); 
		return pow(a,MOD-2); }
		
	mi operator-() const { return mi(-v); }
	mi& operator++() { return *this += 1; }
	mi& operator--() { return *this -= 1; }
	friend mi operator+(mi a, const mi& b) { return a += b; }
	friend mi operator-(mi a, const mi& b) { return a -= b; }
	friend mi operator*(mi a, const mi& b) { return a *= b; }
	friend mi operator/(mi a, const mi& b) { return a /= b; }
};
typedef vector<mi> vmi;
typedef pair<mi,mi> pmi;
typedef vector<pmi> vpmi;

vector<vmi> comb;
void genComb(int SZ) {
	comb.assign(SZ,vmi(SZ)); comb[0][0] = 1;
	FOR(i,1,SZ) F0R(j,i+1) 
		comb[i][j] = comb[i-1][j]+(j?comb[i-1][j-1]:0);
}

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

/**
 * Description: custom bitset
 * Source: Own
 	* Also see https://www.hackerrank.com/contests/noi-ph-2019-finals-1/challenges/sumbong-centers/editorial
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
		return res;
	}
	friend void pr(const bset& x) { F0R(i,x.size) pr((int)x.get(i)); }
	bset& operator|=(const bset& r) {
		assert(size == r.size); F0R(i,sz(b)) b[i] |= r.b[i]; }
	bset& operator&=(const bset& r) {
		assert(size == r.size); F0R(i,sz(b)) b[i] &= r.b[i]; }
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

int main() { 
	// ios_base::sync_with_stdio(0); cin.tie(0); 
	F0R(i,1000) {
		int sz = rand()%1000+1;
		bset t(sz);
		vector<bool> b; F0R(j,sz) b.pb(rand()&1);
		// ps("??",sz,sz(b));
		int num = 0;
		F0R(i,sz(b)) if (b[i]) {
			t.set(i);
			num ++;
			// ps("FLIP",i);
			//ps(t.get(i));
			//exit(0);
		}
		int inc = rand()%sz;
		auto T = t.shift(inc);
		F0R(j,sz) if (b[j] != T.get((j+inc)%sz)) {
			// ps("OOPS",j,(bool)b[j],T.get((j+inc)%sz));
			pr(t); ps(); pr(T);
			exit(0);
		}
		assert(num == T.count());

	}
	F0R(i,1000) {
		int sz = rand()%1000+1;
		bset t(sz);
		set<int> ok;
		F0R(j,rand()%20+1) {
			int pos = rand()%sz;
			t.set(pos);
			ok.insert(pos);
		}
		int a = -1;
		set<int> OK;
		while (a != t.size) {
			OK.insert(a);
			int A = a;
			a = t.findNext(a);
			if (a == A) {
				ps("WHOOPS",a);
				exit(0);
			}
			//ps("HA",a);
		}
		OK.erase(-1);
		assert(ok == OK);
		/*int pos = rand()%sz;
		t.set(pos);
		//ps(t.get(64));
		if (pos != t.findFirst()) {
			ps("AH",sz,pos,t.findFirst());
			exit(0);
		}
		assert(pos == t.findFirst());*/
	}
	//ps(ffs(0),ffs(1),ffs(2),ffs(3));
	//uint64_t u; u += ((uint64_t)1<<63)+(uint64_t)(1<<5);
	//ps((ll)u,__builtin_ffsll(u));
	ps("OK");
	// you should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
*/
