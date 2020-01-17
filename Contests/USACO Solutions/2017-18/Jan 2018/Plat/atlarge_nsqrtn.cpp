// ~1700ms
#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2") // gives RE :(
#pragma GCC target("sse4") // lol this probably doesn't affect

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld; 
typedef double db; 
typedef string str; 

typedef pair<int, int> pi;
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
#define trav(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int MX = 7e4+5; 
const ll INF = 1e18; 
const ld PI = 4*atan((ld)1); 
const int xd[4] = {0,1,0,-1}, yd[4] = {1,0,-1,0}; 

template<class T> bool ckmin(T& a, const T& b) { 
	return a > b ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; }
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

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
		// cin.exceptions(cin.failbit); // ex. throws exception when you try to read letter into int
		if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
	}
}

using namespace io;

struct mi {
	typedef decay<decltype(MOD)>::type T;
	T val; 
	explicit operator T() const { return val; }
	mi() { val = 0; }
	mi(ll v) { 
		val = (-MOD <= v && v <= MOD) ? v : v % MOD;
		if (val < 0) val += MOD;
	}
	friend bool operator==(const mi& a, const mi& b) { 
		return a.val == b.val; }
	friend bool operator!=(const mi& a, const mi& b) { 
		return !(a == b); }
	friend bool operator<(const mi& a, const mi& b) { 
		return a.val < b.val; }
	friend void re(mi& a) { ll x; re(x); a = mi(x); }
	friend void pr(const mi& a) { pr(a.val); }
	friend ostream& operator<<(ostream& os, const mi& a) { 
		return os << a.val; }
   
	mi operator-() const { return mi(-val); }
	mi& operator+=(const mi& m) { 
		if ((val += m.val) >= MOD) val -= MOD; 
		return *this; }
	mi& operator-=(const mi& m) { 
		if ((val -= m.val) < 0) val += MOD; 
		return *this; }
	mi& operator++() { return *this += 1; }
	mi& operator--() { return *this -= 1; }
	friend mi operator+(mi a, const mi& b) { return a += b; }
	friend mi operator-(mi a, const mi& b) { return a -= b; }

	mi& operator*=(const mi& m) { 
		val = (ll)val*m.val%MOD; return *this; }
	friend mi pow(mi a, ll p) {
		mi ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans;
	}
	friend mi inv(const mi& a) { 
		assert(!(a == 0)); return pow(a,MOD-2); }
	mi& operator/=(const mi& m) { return (*this) *= inv(m); }
	friend mi operator*(mi a, const mi& b) { return a *= b; }
	friend mi operator/(mi a, const mi& b) { return a /= b; }
};
typedef pair<mi,mi> pmi;
typedef vector<mi> vmi;
typedef vector<pmi> vpmi;

const int B = 100;

vi adj[MX];
int N,par[MX],st[MX],en[MX],depth[MX],distLeaf[MX],ans[MX];
vi ord;

int cur[MX],dumb[MX];
int csum = 0;
vi inOrd[MX/B+1],val[MX/B+1],dif[MX/B+1];
int add[MX/B+1], ind[MX/B+1];

void dfs(int x) {
	if (sz(adj[x]) == 1) distLeaf[x] = 0;
	else distLeaf[x] = MOD;
	st[x] = sz(ord); ord.pb(x);
	trav(t,adj[x]) if (t != par[x]) {
		par[t] = x; depth[t] = depth[x]+1;
		dfs(t);
		ckmin(distLeaf[x],distLeaf[t]+1);
	}
	en[x] = sz(ord)-1;
}

void build(int z) {
	val[z].clear(), dif[z].clear();
	trav(t,inOrd[z]) {
		if (!sz(val[z]) || val[z].bk != cur[t]) val[z].pb(cur[t]), dif[z].pb(0);
		dif[z].bk += dumb[t];
	}
	ind[z] = ub(all(val[z]),-add[z])-begin(val[z]);
}

void check() {
	int CSUM = 0;
	F0R(i,N) if (cur[i]+add[i/B] > 0) CSUM += dumb[i];
	if (csum != CSUM) {
		ps("AH",csum,CSUM);
		F0R(i,N) ps(i,cur[i]+add[i/B]);
		F0R(i,4) ps(i,sz(val[i]),val[i],add[i],ind[i]);
		exit(0);
	}
}

int todo[MX];

void upd(int R, int inc) {
	//ps("UPD",R,inc);
	//F0R(i,N) ps(i,cur[i]+add[i]);
	if ((R+1)%B != 0 && R != N-1) {
		int z = R/B; int RR = R;
		while ((R+1)%B != 0) {
			if (cur[R]+add[z] > 0) csum -= dumb[R];
			cur[R] += inc; 
			if (cur[R]+add[z] > 0) csum += dumb[R];
			R --;
		}
		vi a,b;
		trav(t,inOrd[z]) {
			if (t <= RR) a.pb(t);
			else b.pb(t);
		}
		inOrd[z].clear();
		int ia = 0, ib = 0;
		while (ia < sz(a) && ib < sz(b)) {
			if (cur[a[ia]] < cur[b[ib]]) inOrd[z].pb(a[ia++]);
			else inOrd[z].pb(b[ib++]);
		}
		while (ia < sz(a)) inOrd[z].pb(a[ia++]);
		while (ib < sz(b)) inOrd[z].pb(b[ib++]);
		build(z);
	}
	if (R >= 0) {
		int z = R/B; // ps("COOL",R,inc,z);
		F0R(i,z+1) todo[i] += inc;
	}
}

void close(int t, int b) {
	upd(N-1,-b);
	upd(en[t],2*b);
	upd(st[t]-1,-2*b);
	F0R(z,(N-1)/B+1) {
		int inc = todo[z]; if (!inc) continue;
		add[z] += inc; todo[z] = 0;
		if (inc > 0) {
			if (ind[z] && val[z][ind[z]-1]+add[z] > 0) {
				csum += dif[z][--ind[z]];
			}
		} else {
			if (ind[z] < sz(val[z]) && val[z][ind[z]]+add[z] <= 0) {
				csum -= dif[z][ind[z]++];
			}
		}
	}
}

void solve(int x) {
	if (sz(adj[x]) == 1) ans[x] = 1;
	else ans[x] = csum+2;
	trav(t,adj[x]) if (t != par[x] && sz(adj[t]) != 1) {
		close(t,1);
		solve(t);
		close(t,-1);
	}
}

int main() {
	// setIO();
	setIO("atlarge");
	re(N);
	F0R(i,N-1) {
		int a,b; re(a,b);
		adj[a].pb(b), adj[b].pb(a);
	}
	dfs(1);
	trav(t,ord) if (par[t]) ckmin(distLeaf[t],distLeaf[par[t]]+1);

	F0R(i,MX/B+1) dif[i].reserve(B), val[i].reserve(B);
	// FOR(i,1,N+1) ps(i,distLeaf[i],st[i],en[i]);
	vi cnt(2*N+1);
	FOR(i,1,N+1) {
		dumb[st[i]] = sz(adj[i])-2;
		cur[st[i]] = distLeaf[i]-depth[i];
		cnt[cur[st[i]]+N] ++;
	}
	int sum = 0;
	F0R(i,2*N+1) {
		swap(sum,cnt[i]);
		sum += cnt[i];
	}
	vi ord(N,-1);
	F0R(i,N) {
		ord[cnt[cur[i]+N]++] = i;
		if (cur[i] > 0) csum += dumb[i];
	}
	trav(t,ord) inOrd[t/B].pb(t);
	for (int i = 0; i < N; i += B) {
		int z = i/B;
		//FOR(j,i,min(i+B,N)) inOrd[z].pb(j);
		//sort(all(inOrd[z]),[](int a, int b) { return cur[a] < cur[b]; });
		build(z);
	}
	solve(1);
	FOR(i,1,N+1) {
		if (!ans[i]) ans[i] = 1;
		ps(ans[i]);
	}
	// you should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?), slow multiset operations
	* do smth instead of nothing and stay organized
*/