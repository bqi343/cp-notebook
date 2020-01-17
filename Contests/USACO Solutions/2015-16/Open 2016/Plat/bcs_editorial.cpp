// lol apparently R,C <= 100 in statement is FALSE
// WORST USACO MONTHLY PROBLEM lol

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
const int MX = 2e5+5; 
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

typedef array<mi,2> T; // pick bases not too close to ends
uniform_int_distribution<int> MULT_DIST(0.1*MOD,0.9*MOD); 

T ID = {1,1};
T rig = {MULT_DIST(rng),MULT_DIST(rng)};
T dow = {MULT_DIST(rng),MULT_DIST(rng)};
T rigP[501], dowP[501];

T operator+(const T& l, const T& r) { T x; 
	F0R(i,2) x[i] = l[i]+r[i]; 
	return x; }
T operator-(const T& l, const T& r) { T x; 
	F0R(i,2) x[i] = l[i]-r[i]; 
	return x; }
T operator*(const T& l, const T& r) { T x; 
	F0R(i,2) x[i] = l[i]*r[i]; 
	return x; }

T& operator+=(T& l, const T& r) { return l = l+r; }
T& operator-=(T& l, const T& r) { return l = l-r; }
T& operator*=(T& l, const T& r) { return l = l*r; }
// http://www.usaco.org/index.php?page=viewproblem2&cpid=649

T offset(T a, pi b) {
	return a*dowP[b.f]*rigP[b.s];
}

int val(char c) {
	if (c == '.') return 0;
	return c-'a'+100;
}
T get(char c) {
	return {val(c),val(c)};
}

int K;
int* cumR[800];
array<int,500*500> CUMR;

T getHash(const vs& v) {
	T h = {0,0};
	F0R(i,sz(v)) F0R(j,sz(v[0])) h += offset(get(v[i][j]),{i,j});
	return h;
}

struct hsh {
	int R,C; 
	int fst = -1;
	T h;
	void gen(const vs& v, int ind) {
		R = sz(v), C = sz(v[0]);
		F0R(j,C) if (v[0][j] != '.') {
			fst = j;
			break;
		}
		if (ind == -1) {
			F0R(i,R) {
				F0R(j,C) {
					int h = C*i+j;
					CUMR[h] = v[i][j] != '.';
					if (h) CUMR[h] += CUMR[h-1];
				}
			}
		} else {
			cumR[ind] = new int[R*C];
			F0R(i,R) {
				F0R(j,C) {
					int h = C*i+j;
					cumR[ind][h] = v[i][j] != '.';
					if (h) cumR[ind][h] += cumR[ind][h-1];
				}
			}
		}
		h = getHash(v);
	}
};

hsh st, stor[800];
bool ok[100][100][100];

void ins(vi v) {
	sort(all(v));
	trav(t,v) t /= 8;
	ok[v[0]][v[1]][v[2]] = 1;
}

vs compress(vs v) {
	pi x = {MOD,-MOD}, y = {MOD,-MOD};
	F0R(i,sz(v)) {
		F0R(j,sz(v[0])) if (v[i][j] != '.') {
			ckmin(x.f,i), ckmax(x.s,i);
			ckmin(y.f,j), ckmax(y.s,j);
		}
	}
	vs res(x.s-x.f+1,str(y.s-y.f+1,'.'));
	FOR(i,x.f,x.s+1) FOR(j,y.f,y.s+1) res[i-x.f][j-y.f] = v[i][j];
	return res;
}

pi getFirst(vector<pair<int,pi>> v) {
	int lo = 0, hi = st.R*st.C;
	while (lo < hi) {
		int mid = (lo+hi)/2;
		int r = mid/st.C, c = mid%st.C;
		int a = CUMR[mid];
		trav(t,v) {
			int rr = r-t.s.f, cc = c-t.s.s;
			if (cc < 0) rr --, cc = MOD;
			if (rr < 0) continue;
			ckmin(cc,stor[t.f].C-1);
			if (rr >= stor[t.f].R) { a -= cumR[t.f][stor[t.f].R*stor[t.f].C-1]; continue; }
			a -= cumR[t.f][rr*stor[t.f].C+cc];
		}
		if (a == 0) lo = mid+1;
		else hi = mid;
	}
	if (lo == st.R*st.C) return {MOD,MOD};
	return {lo/st.C,lo%st.C};
}

map<T,int> m;
int oc[100];

void prin(vs v) {
	trav(t,v) ps(t);
	ps("-----");
}

int cnt = 0;

void search(vector<pair<int,pi>> v) {
	pi p = getFirst(v); if (p == mp(MOD,MOD)) return;
	//ps("AH",v,p);
	if (sz(v) == 2) {
		auto a = st.h; trav(t,v) a -= offset(stor[t.f].h,t.s);
		a = offset(a,{st.R-p.f,st.C-p.s});
		if (m.count(a)) ins({v[0].f,v[1].f,8*m[a]});
		return;
	}
	F0R(i,cnt) {
		auto V = v; 
		pi offset = {p.f,p.s-stor[i].fst};
		//ps("OH",v,i,offset,p,stor[i].fst,stor[i].v);
		if (offset.s < 0 
			|| offset.f+stor[i].R > st.R
			|| offset.s+stor[i].C > st.C)
			continue;
		V.pb({i,offset});
		search(V);
	}
}

vs rot(vs v) {
	vs V(sz(v[0]),string(sz(v),'.'));
	F0R(i,sz(v)) F0R(j,sz(v[0])) {
		V[j][sz(v)-1-i] = v[i][j];
	}
	return V;
}

vs flip(vs v) {
	vs V(sz(v),string(sz(v[0]),'.'));
	F0R(i,sz(v)) F0R(j,sz(v[0])) {
		V[sz(v)-1-i][j] = v[i][j];
	}
	return V;
}

int num = 0;

void init() {
	setIO("bcs");
	rigP[0] = ID; FOR(i,1,501) rigP[i] = rigP[i-1]*rig;
	dowP[0] = ID; FOR(i,1,501) dowP[i] = dowP[i-1]*dow;
	re(K); 
	int r,c; re(r,c);
	vs v(r); F0R(j,r) re(v[j]);
	v = compress(v); st.gen(v,-1);
	F0R(i,K) {
		int r,c; re(r,c);
		vs v(r); F0R(j,r) re(v[j]);
		v = compress(v);
		int fst = 0; while (v[0][fst] == '.') fst ++;
		auto p = offset(getHash(v),{st.R,st.C-fst});
		if (m.count(p)) {
			oc[m[p]] ++;
			continue;
		}
		oc[num] ++;
		F0R(j,4) {
			stor[cnt].gen(v,cnt);
			m[offset(stor[cnt].h,{st.R,st.C-stor[cnt].fst})] = num;
			v = rot(v);
			cnt ++;
		}
		v = flip(v);
		F0R(j,4) {
			stor[cnt].gen(v,cnt);
			m[offset(stor[cnt].h,{st.R,st.C-stor[cnt].fst})] = num;
			v = rot(v);
			cnt ++;
		}
		num ++;
	}
	// ps(num); exit(0);
}

int main() {
	init();
	/*T t = dowP[5]*rigP[5]+dowP[6]*(rigP[3]+rigP[4]+rigP[5]+rigP[6]+rigP[7]);
	t *= get('a');
	// ps("TESTING",t);*/
	// clock_t beg = clock();
	search({});
	int ans = 0;
	F0R(i,num) FOR(j,i,num) FOR(k,j,num) if (ok[i][j][k]) {
		if (i == j && j == k) ans += oc[i]*(oc[i]-1)*(oc[i]-2)/6;
		else if (i == j) ans += oc[i]*(oc[i]-1)/2*oc[k];
		else if (j == k) ans += oc[i]*oc[j]*(oc[j]-1)/2;
		else ans += oc[i]*oc[j]*oc[k];
		// if (ok[i][j][k]) ps("WUT",i,j,k);
	}
	// ps((db)(clock()-beg)/CLOCKS_PER_SEC);
	ps(ans);
	// you should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?), slow multiset operations
	* do smth instead of nothing and stay organized
*/