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
#define trav(a,x) for (auto& a: x)

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
const int MX = 70005;
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

template<int SZ> struct CD {
    vi adj[SZ];
    bool done[SZ]; 
    int sub[SZ], par[SZ]; // subtree size, current par
    pi cen[SZ]; // immediate centroid anc
    vi dist[SZ]; // dists to all centroid ancs
    void addEdge(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
    void dfs(int x) {
        sub[x] = 1;
        trav(y,adj[x]) if (!done[y] && y != par[x]) {
            par[y] = x; dfs(y);
            sub[x] += sub[y];
        }
    }
    int centroid(int x) {
        par[x] = -1; dfs(x); 
        for (int sz = sub[x];;) {
            pi mx = {0,0};
            trav(y,adj[x]) if (!done[y] && y != par[x]) 
                ckmax(mx,{sub[y],y});
            if (mx.f*2 <= sz) return x; 
            x = mx.s;
        }
    }
    int maxDist;
    void genDist(int x, int p) {
        dist[x].pb(dist[p].back()+1);
        ckmax(maxDist,dist[x].back());
        trav(y,adj[x]) if (!done[y] && y != p) genDist(y,x); 
    }
    void gen(pi CEN, int x) {
        done[x = centroid(x)] = 1; cen[x] = CEN; 
        dist[x].pb(0); int co = 0;
        int mx = 0;
        trav(y,adj[x]) if (!done[y]) {
            maxDist = 0;
            genDist(y,x);
            STOR[x].eb(); STOR[x].back().rsz(maxDist+1);
            ckmax(mx,maxDist);
        }
        stor[x].rsz(mx+1);
        trav(y,adj[x]) if (!done[y]) gen({x,co++},y);
    }
    void init() { gen({0,0},1); }
    vi stor[MX];
    vector<vi> STOR[MX];
    void ad(vi& a, int b, int c) {
        if (b < 0) return;
        a[min(b,sz(a)-1)] += c;
    }
    int query(vi& a, int b) {
        if (b >= sz(a)) return 0;
        return a.back()-(b==0?0:a[b-1]);
    }
    void upd(int x, int d, int v) {
        pi CEN = {x,-1}; int ind = sz(dist[x])-1;
        while (CEN.f) {
            ad(stor[CEN.f],d-dist[x][ind],v);
            if (CEN.s != -1) ad(STOR[CEN.f][CEN.s],d-dist[x][ind],v);
            ind --; CEN = cen[CEN.f];
        }
    }
    int query(int x) {
        pi CEN = {x,-1}; int ind = sz(dist[x])-1;
        int ans = 0;
        while (CEN.f) {
            ans += query(stor[CEN.f],dist[x][ind]);
            if (CEN.s != -1) ans -= query(STOR[CEN.f][CEN.s],dist[x][ind]);
            ind --; CEN = cen[CEN.f];
        }
        return ans;
    }
};
CD<MX> C;

int n,dist[MX],par[MX];
vi adj[MX];
vi ord;

void dfs(int x) {
    ord.pb(x);
    trav(t,adj[x]) if (t != par[x]) {
        par[t] = x;
        dfs(t);
    }
}

void init(vi& v) {
    FOR(i,1,sz(v)) v[i] += v[i-1];
}

int main() {
    setIO("atlarge");
    re(n);
    F0R(i,n-1) {
        int a,b; re(a,b);
        adj[a].pb(b), adj[b].pb(a);
        C.addEdge(a,b);
    }
    C.init();
    dfs(1);
    FOR(i,1,n+1) {
        if (sz(adj[i]) == 1) dist[i] = 0;
        else dist[i] = MOD;
    }
    ROF(i,1,sz(ord)) ckmin(dist[par[ord[i]]],dist[ord[i]]+1);
    trav(a,ord) trav(b,adj[a]) if (par[b] == a) ckmin(dist[b],dist[a]+1);
    FOR(i,1,n+1) C.upd(i,dist[i]-1,sz(adj[i])-2);
    FOR(i,1,n+1) {
        init(C.stor[i]);
        trav(t,C.STOR[i]) init(t);
    }
    FOR(i,1,n+1) {
        if (dist[i] == 0) ps(1);
        else ps(C.query(i)+2); 
        // consider subtree that consists of nodes that are closer to i
        // than to any leaf, then sum_v(deg(v)-2)+2 gives # of edges which
        // exit subtree, which is what we want
    }
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), slow multiset operations
    * do smth instead of nothing and stay organized
*/