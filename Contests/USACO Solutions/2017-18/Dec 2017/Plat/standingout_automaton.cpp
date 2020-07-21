#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; 
typedef string str; 

typedef pair<int,int> pi;
typedef pair<ll,ll> pl; 
typedef pair<db,db> pd; 

typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef vector<db> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 

#define mp make_pair
#define f first
#define s second
#define sz(x) (int)(x).size()
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

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5; 
const ll INF = 1e18; 
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; 
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

template<class T> bool ckmin(T& a, const T& b) { 
	return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; } 
constexpr int pct(int x) { return __builtin_popcount(x); } 
constexpr int bits(int x) { return 31-__builtin_clz(x); } // floor(log2(x)) 
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
ll half(ll x) { return fdiv(x,2); }

template<class T, class U> T fstTrue(T lo, T hi, U f) {
	hi ++; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true 
		T mid = half(lo+hi);
		f(mid) ? hi = mid : lo = mid+1; 
	} 
	return lo;
}
template<class T, class U> T lstTrue(T lo, T hi, U f) {
	lo --; assert(lo <= hi); // assuming f is decreasing
	while (lo < hi) { // find first index such that f is true 
		T mid = half(lo+hi+1);
		f(mid) ? lo = mid : hi = mid-1;
	} 
	return lo;
}
template<class T> void remDup(vector<T>& v) { 
	sort(all(v)); v.erase(unique(all(v)),end(v)); }

// INPUT
template<class A> void re(complex<A>& c);
template<class A, class B> void re(pair<A,B>& p);
template<class A> void re(vector<A>& v);
template<class A, size_t SZ> void re(array<A,SZ>& a);

template<class T> void re(T& x) { cin >> x; }
void re(db& d) { str t; re(t); d = stod(t); }
void re(ld& d) { str t; re(t); d = stold(t); }
template<class H, class... T> void re(H& h, T&... t) { re(h); re(t...); }

template<class A> void re(complex<A>& c) { A a,b; re(a,b); c = {a,b}; }
template<class A, class B> void re(pair<A,B>& p) { re(p.f,p.s); }
template<class A> void re(vector<A>& x) { trav(a,x) re(a); }
template<class A, size_t SZ> void re(array<A,SZ>& x) { trav(a,x) re(a); }

// TO_STRING
#define ts to_string
str ts(char c) { return str(1,c); }
str ts(const char* s) { return (str)s; }
str ts(str s) { return s; }
str ts(bool b) { 
	#ifdef LOCAL
		return b ? "true" : "false"; 
	#else 
		return ts((int)b);
	#endif
}
template<class A> str ts(complex<A> c) { 
	stringstream ss; ss << c; return ss.str(); }
str ts(vector<bool> v) {
	str res = "{"; F0R(i,sz(v)) res += char('0'+v[i]);
	res += "}"; return res; }
template<size_t SZ> str ts(bitset<SZ> b) {
	str res = ""; F0R(i,SZ) res += char('0'+b[i]);
	return res; }
template<class A, class B> str ts(pair<A,B> p);
template<class T> str ts(T v) { // containers with begin(), end()
	#ifdef LOCAL
		bool fst = 1; str res = "{";
		for (const auto& x: v) {
			if (!fst) res += ", ";
			fst = 0; res += ts(x);
		}
		res += "}"; return res;
	#else
		bool fst = 1; str res = "";
		for (const auto& x: v) {
			if (!fst) res += " ";
			fst = 0; res += ts(x);
		}
		return res;

	#endif
}
template<class A, class B> str ts(pair<A,B> p) {
	#ifdef LOCAL
		return "("+ts(p.f)+", "+ts(p.s)+")"; 
	#else
		return ts(p.f)+" "+ts(p.s);
	#endif
}

// OUTPUT
template<class A> void pr(A x) { cout << ts(x); }
template<class H, class... T> void pr(const H& h, const T&... t) { 
	pr(h); pr(t...); }
void ps() { pr("\n"); } // print w/ spaces
template<class H, class... T> void ps(const H& h, const T&... t) { 
	pr(h); if (sizeof...(t)) pr(" "); ps(t...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class H, class... T> void DBG(H h, T... t) {
	cerr << ts(h); if (sizeof...(t)) cerr << ", ";
	DBG(t...); }
#ifdef LOCAL // compile with -DLOCAL
	#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
	#define dbg(...) 0
#endif

// FILE I/O
void setIn(str s) { freopen(s.c_str(),"r",stdin); }
void setOut(str s) { freopen(s.c_str(),"w",stdout); }
void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }
void setIO(str s = "") {
	unsyncIO();
	// cin.exceptions(cin.failbit); 
	// throws exception when do smth illegal
	// ex. try to read letter into int
	if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
}

int comb(int a, int b) {
	if (min(a,b) == -1) return max(a,b);
	return a == b ? a : MOD;
}

struct SuffixAutomaton {
	struct state {
		int len = 0, link = -1, label = -1;
		map<char, int> next;
		vi invLink;
	}; vector<state> st;
	int add(int p, char c) {
		int q;
		auto redirect = [&]() {
			int clone = sz(st); st.pb(st[q]); st[clone].len = st[p].len+1;
			st[q].link = clone;
			for (; ~p && st[p].next[c] == q; p = st[p].link) 
				st[p].next[c] = clone;
			return clone;
		};
		if (st[p].next.count(c)) {
			int len = st[p].len+1; q = st[p].next[c]; if (st[q].len == len) return q;
			return redirect();
		}
		int cur = sz(st); st.eb(); st[cur].len = st[p].len+1;
		for (; ~p && !st[p].next.count(c); p = st[p].link) 
			st[p].next[c] = cur; // create new transitions
		if (p == -1) return st[cur].link = 0, cur;
		// suffix link for cur should have length st[p].len+1
		int len = st[p].len+1; 
		q = st[p].next[c]; if (st[q].len == len) return st[cur].link = q, cur;
		int clone = redirect(); st[cur].link = clone;
		return cur;
		// len[link[link[lst]]] decreases for each iteration of this loop
	} // -> amortized linear
	// void init(str s) { 
	// 	st.eb(); trav(x,s) add(x); 
	// 	FOR(v,1,sz(st)) st[st[v].link].invLink.pb(v);
	// }
	// // APPLICATIONS
	// void getAllOccur(vi& oc, int v) {
	// 	if (!st[v].isClone) oc.pb(st[v].pos);
	// 	trav(u,st[v].invLink) getAllOccur(oc,u);
	// }
	// vi allOccur(str s) {
	// 	int cur = 0;
	// 	trav(x,s) {
	// 		if (!st[cur].next.count(x)) return {};
	// 		cur = st[cur].next[x];
	// 	}
	// 	vi oc; getAllOccur(oc,cur); trav(t,oc) t += 1-sz(s);
	// 	sort(all(oc)); return oc;
	// }
	// vl distinct;
	// ll getDistinct(int x) {
	// 	if (distinct[x]) return distinct[x];
	// 	distinct[x] = 1; 
	// 	trav(y,st[x].next) distinct[x] += getDistinct(y.s);
	// 	return distinct[x];
	// }
	// ll numDistinct() { // # distinct substrings including empty
	// 	distinct.rsz(sz(st)); return getDistinct(0); }
	// ll numDistinct2() { // another way to do above
	// 	ll ans = 1;
	// 	FOR(i,1,sz(st)) ans += st[i].len-st[st[i].link].len;
	// 	return ans; }
	vi topo;
	void dfs(int x) {
		trav(t,st[x].invLink) {
			assert(st[x].len < st[t].len);
			dfs(t);
			st[x].label = comb(st[x].label,st[t].label);
		}
	}
	vector<bool> vis;
	void dfs2(int x) {
		if (!sz(vis)) vis.rsz(sz(st));
		if (vis[x]) return;
		vis[x] = 1; trav(t,st[x].next) dfs2(t.s);
		topo.pb(x);
	}
};

SuffixAutomaton S;

int N;
vl ways;
vs v;

int main() {
	S.st.rsz(1);
	setIO("standingout"); re(N); 
	F0R(i,N) {
		str s; re(s);
		int p = 0;
		trav(c,s) {
			p = S.add(p,c); dbg(i,c,p);
			S.st[p].label = comb(S.st[p].label,i);
		}
	}
	//exit(0);
	vi ans(N);
	FOR(i,1,sz(S.st)) S.st[S.st[i].link].invLink.pb(i);
	//dbg("OK"); exit(0);
	S.dfs(0); S.dfs2(0);
	reverse(all(S.topo));
	assert(S.topo[0] == 0);
	dbg(S.topo);
	ways.rsz(sz(S.st)); ways[0] = 1;
	F0R(i,sz(S.topo)) {
		int x = S.topo[i];
		trav(t,S.st[x].next) ways[t.s] += ways[x];
		if (S.st[x].label != MOD) ans[S.st[x].label] += ways[x];
	}
	F0R(i,N) ps(ans[i]);
	// you should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

