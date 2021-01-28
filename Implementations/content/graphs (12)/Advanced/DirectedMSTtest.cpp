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
		ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
		// cin.exceptions(cin.failbit); // ex. throws exception when you try to read letter into int
		if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
	}
}

using namespace io;

typedef decay<decltype(MOD)>::type T;
struct mi {
	T val; 
	explicit operator T() const { return val; }
	mi() { val = 0; }
	mi(const ll& v) { 
		val = (-MOD <= v && v <= MOD) ? v : v % MOD;
		if (val < 0) val += MOD;
	}
	// friend ostream& operator<<(ostream& os, const mi& a) { 
		// return os << a.val; }
	friend void pr(const mi& a) { pr(a.val); }
	friend void re(mi& a) { ll x; re(x); a = mi(x); }
   
	friend bool operator==(const mi& a, const mi& b) { 
		return a.val == b.val; }
	friend bool operator!=(const mi& a, const mi& b) { 
		return !(a == b); }
	friend bool operator<(const mi& a, const mi& b) { 
		return a.val < b.val; }

	mi operator-() const { return mi(-val); }
	mi& operator+=(const mi& m) { 
		if ((val += m.val) >= MOD) val -= MOD; 
		return *this; }
	mi& operator-=(const mi& m) { 
		if ((val -= m.val) < 0) val += MOD; 
		return *this; }
	mi& operator*=(const mi& m) { 
		val = (ll)val*m.val%MOD; return *this; }
	friend mi pow(mi a, ll p) {
		mi ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans;
	}
	friend mi inv(const mi& a) { 
		assert(a != 0); return pow(a,MOD-2); }
	mi& operator/=(const mi& m) { return (*this) *= inv(m); }
	
	friend mi operator+(mi a, const mi& b) { return a += b; }
	friend mi operator-(mi a, const mi& b) { return a -= b; }
	friend mi operator*(mi a, const mi& b) { return a *= b; }
	friend mi operator/(mi a, const mi& b) { return a /= b; }
};

typedef pair<mi,mi> pmi;
typedef vector<mi> vmi;
typedef vector<pmi> vpmi;

struct DSUrb {
	vi e;
	void init(int n) { e = vi(n,-1); }
	int get(int x) { return e[x] < 0 ? x : get(e[x]); } // path compression
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	vector<array<int,4>> mod;
	bool unite(int x, int y) { // union-by-rank
		x = get(x), y = get(y); 
		if (x == y) {
			mod.pb({MOD,MOD,MOD,MOD});
			return 0;
		}
		if (e[x] > e[y]) swap(x,y);
		mod.pb({x,y,e[x],e[y]});
		e[x] += e[y]; e[y] = x;
		return 1;
	}
	void rollback() {
		auto a = mod.back(); mod.pop_back();
		if (a[0] != MOD) e[a[0]] = a[2], e[a[1]] = a[3];
	}
};

struct Edge { 
	int a, b; ll w; 
	friend void pr(const Edge& e) { pr(vl{e.a,e.b,e.w}); }
};

struct Node { /// lazy skew heap node
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

pair<ll,vi> dmst(int n, int r, const vector<Edge>& g) {
	DSUrb dsu; dsu.init(n); 
	vector<Node*> heap(n); // store edges entering each vertex 
	// in increasing order of weight
	each(e,g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0; vi seen(n,-1); seen[r] = r; 
	vpi in(n,{-1,-1}); // edge entering each vertex in MST
	vector<pair<int,vector<Edge>>> cycs;
	F0R(s,n) {
		int u = s, w;
		vector<pair<int,Edge>> path; 
		while (seen[u] < 0) {
			if (!heap[u]) return {-1,{}};
			seen[u] = s;
			Edge e = heap[u]->top(); path.pb({u,e}); 
			heap[u]->delta -= e.w, pop(heap[u]);
			res += e.w, u = dsu.get(e.a); 
			if (seen[u] == s) { // found cycle
				Node* cyc = 0; cycs.eb();
				do {
					cyc = merge(cyc, heap[w = path.back().f]);
					cycs.back().s.pb(path.back().s);
					path.pop_back(); 
				} while (dsu.unite(u,w));
				u = dsu.get(u); heap[u] = cyc, seen[u] = -1;
				cycs.back().f = u;
			}
		}
		each(t,path) in[dsu.get(t.s.b)] = {t.s.a,t.s.b}; 
		// found path from root
	}
	while (sz(cycs)) { // expand cycs to restore sol
		auto c = cycs.back(); cycs.pop_back();
		pi inEdge = in[c.f];
		each(t,c.s) dsu.rollback();
		each(t,c.s) in[dsu.get(t.b)] = {t.a,t.b};
		in[dsu.get(inEdge.s)] = inEdge;
	}
	vi inv; 
	F0R(i,n) { 
		assert(i == r ? in[i].s == -1 : in[i].s == i);
		inv.pb(in[i].f); 
	} 
	return {res,inv};
}

ll dmstKACTL(int n, int r, const vector<Edge>& g) {
	DSUrb dsu; dsu.init(n);
	vector<Node*> heap(n);
	each(e, g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	vi seen(n, -1), path(n); seen[r] = r;
	F0R(s,n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			path[qi++] = u, seen[u] = s;
			if (!heap[u]) return -1;
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			res += e.w, u = dsu.get(e.a);
			if (seen[u] == s) {
				Node* cyc = 0;
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (dsu.unite(u, w));
				u = dsu.get(u);
				heap[u] = cyc, seen[u] = -1;
			}
		}
	}
	return res;
}

int adj[105][105];

int main() {
	/*int n = 4, r = 1;
	vector<tuple<int, int, int>> data = {
		{0, 3, 27},
		{1, 2, 32},
		{2, 3, 25},
		{3, 0, 31},
		{3, 2, 23},
	};
	vector<Edge> edges;
	each(e, data) {
		int a = get<0>(e);
		int b = get<1>(e);
		int w = get<2>(e);
		edges.push_back({a, b, w});
	}

	dmst(n, r, edges);*/
	int cnt = 0;
	F0R(it,100000) {
		int n = (rand()%20)+1;
		int density = rand() % 101;
		int r = rand()%n;
		vector<Edge> g;
		F0R(i,n) F0R(j,n) {
			if (i == j) continue;
			if (rand() % 100 >= density) continue;
			int weight = rand()%100;
			g.pb({i,j,weight});
			adj[i][j] = weight;
		}
		auto ans = dmst(n,r,g);
		assert(ans.f == dmstKACTL(n,r,g));
		if (ans.f != -1) {
			cnt ++;
			vi par = ans.s;
			ll sum = 0;
			vector<vi> ch(n);
			F0R(i,n) {
				if (i == r) assert(par[i] == -1);
				else {
					assert(par[i] != -1);
					sum += adj[par[i]][i];
					ch[par[i]].push_back(i);
				}
			}
			assert(sum == ans.f);
			vi seen(n), q = {r};
			F0R(qi,sz(q)) {
				int s = q[qi];
				if (!seen[s]++)
					each(x, ch[s]) q.push_back(x);
			}
			assert(count(all(seen), 0) == 0);
		}
	}
	ps(cnt);
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?), slow multiset operations
	* do smth instead of nothing and stay organized
*/
