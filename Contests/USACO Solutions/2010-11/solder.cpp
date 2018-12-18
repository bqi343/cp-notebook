/*
ID: bqi3431
PROG: solder
LANG: C++11 
*/

#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<int,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 50001;
const ld PI = 4*atan((ld)1);

template<class T> void ckmin(T &a, T b) { a = min(a, b); }
template<class T> void ckmax(T &a, T b) { a = max(a, b); }

namespace io {
    // TYPE ID (StackOverflow)
    
    template<class T> struct like_array : is_array<T>{};
    template<class T, size_t N> struct like_array<array<T,N>> : true_type{};
    template<class T> struct like_array<vector<T>> : true_type{};
    template<class T> bool is_like_array(const T& a) { return like_array<T>::value; }

    // I/O 
    
    void setIn(string s) { freopen(s.c_str(),"r",stdin); }
    void setOut(string s) { freopen(s.c_str(),"w",stdout); }
    void setIO(string s = "") {
        ios_base::sync_with_stdio(0); cin.tie(0);
        if (sz(s)) { setIn(s+".in"), setOut(s+".out"); }
    }
    
    // INPUT 
    
    template<class T> void re(T& x) { cin >> x; }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest);
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);
    
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) { re(first); re(rest...); }
    template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = cd(a,b); }
    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
    
    // OUTPUT 
    
    template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) {
        os << '{' << a.f << ", " << a.s << '}'; return os;
    }
    template<class T> ostream& printArray(ostream& os, const T& a, int SZ) {
        os << '{';
        F0R(i,SZ) {
            if (i) {
                os << ", ";
                if (is_like_array(a[i])) cout << "\n";
            }
            os << a[i];
        }
        os << '}';
        return os;
    }
    template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
        return printArray(os,a,sz(a));
    }
    template<class T, size_t SZ> ostream& operator<<(ostream& os, const array<T,SZ>& a) {
        return printArray(os,a,SZ);
    }
    
    template<class T> void pr(const T& x) { cout << x << '\n'; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) { 
        cout << first << ' '; pr(rest...); 
    }
}

using namespace io;

bool Q;

struct Line {
    mutable ll k, m, p; // slope, y-intercept, last optimal x
    bool operator<(const Line& o) const {
        return Q ? p < o.p : k < o.k;
    }
    ll get(ll x) { return k*x+m; }
};

struct LineContainer : multiset<Line> { 
    const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { // floored division
        if (b < 0) a *= -1, b *= -1;
        if (a >= 0) return a/b;
        return -((-a+b-1)/b);
    }
    
    // updates x->p, determines if y is unneeded
    bool isect(iterator x, iterator y) { 
        if (y == end()) { x->p = inf; return 0; }
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    
    void add(ll k, ll m) {
        k *= -1, m *= -1;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    
    ll query(ll x) { 
        assert(!empty());
        Q = 1; auto l = *lb({0,0,x}); Q = 0;
        return - (l.k * x + l.m);
    }
}; // query minimum

struct state {
    ll offset = 0;
    pl ad = {0,0};
    LineContainer L;
    vpl lines;
    
    void ins(pl a) {
        a.f -= ad.f/2; a.s -= ad.s+(ad.f+2*a.f)*offset;
        // 2*a.f*(x+offset)+ad.f*(x+offset)+ad.s+a.s 
        // equivalent to 2*a.f*x+a.s 
        lines.pb({a.f,a.s});
        L.add(2*a.f,a.s);
    }
    
    ll query(ll x) {
        return L.query(x+offset)+ad.f*(x+offset)+ad.s;
    }
    
    vpl actual() {
        vpl res;
        trav(z,lines) res.pb({z.f+ad.f/2,(2*z.f+ad.f)*offset+ad.s+z.s});
        return res;
    }
    
    void clear() {
        offset = 0; ad = {0,0};
        L.clear(); lines.clear();
    }
    
    int size() { return sz(lines); }
};

void swap(state& a, state& b) {
    swap(a.offset,b.offset);
    swap(a.ad,b.ad);
    swap(a.L,b.L);
    swap(a.lines,b.lines);
}

pl operator+(const pl& l, const pl& r) { return {l.f+r.f,l.s+r.s}; }
pl operator+=(pl& l, const pl& r) { return l = l+r; }

state cur[MX];
int n;
vi adj[MX];

void ad(int x) {
    cur[x].ad += mp(2,-1-2*cur[x].offset);
    cur[x].offset ++; 
}

// 0 -> 0 (add constant)
// 0 -> 1 
// 1 -> 1 (add constant)
// 1 -> 1 

ll sum;
state Z;

void comb(int x) {
    //pr(x,cur[x].actual());
    ll st = cur[x].query(0);
    vpl v;
    ll bes = INF;
    if (sz(Z) < sz(cur[x])) {
        trav(t,Z.actual()) {
            ckmin(bes,t.s+cur[x].query(t.f));
            v.pb({0,t.s+cur[x].query(t.f)}); // Z+cur[x],
            v.pb({t.f,t.s+st});
        }
        if (bes < INF) v.pb({0,bes});
        cur[x].ad.s += sum;
        trav(t,v) cur[x].ins(t);
        swap(Z,cur[x]);
    } else {
        trav(t,cur[x].actual()) {
            ckmin(bes,t.s+Z.query(t.f));
            v.pb({t.f,t.s+sum}); // sum+cur[x]
        }
        if (bes < INF) v.pb({0,bes});
        Z.ad.s += st;
        trav(t,v) Z.ins(t); // Z+cur[x].query(0), 
    }
    cur[x].clear();
    sum += st;
}

void dfs(int a, int b) {
    // combine two offsettrees, add edge to top 
    int child = 0;
    trav(x,adj[a]) if (x != b) {
        dfs(x,a); 
        ad(x); 
        child ++;
    }
    if (child == 0) {
        cur[a].ins({0,0});
    } else {
        sum = 0; assert(!sz(Z));
        trav(x,adj[a]) if (x != b) {
            // pr("HUH",x,cur[x].actual(),cur[x].query(5));
            comb(x);
        }
        swap(cur[a],Z);
        // pr(sum,cur[a].actual());
    }
    //pr("BLAH",a,cur[a].actual());
}

int main() {
    // you should actually read the stuff at the bottom
    setIO("solder"); 
    re(n);
    F0R(i,n-1) {
        int a,b; re(a,b);
        adj[a].pb(b), adj[b].pb(a);
    }
    dfs(1,0);
    ll ret = INF; 
    trav(t,cur[1].actual()) {
        if (sz(adj[1]) == 1) {
            ckmin(ret,t.s);
        } else {
            if (!t.f) ckmin(ret,t.s);
        }
    }
    pr(ret);
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
