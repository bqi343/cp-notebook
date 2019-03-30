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
typedef pair<ll,ll> pl;
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

const int MOD = 1000000007; // 998244353
const ll INF = 1e18;
const int MX = 200005;
const ld PI = 4*atan((ld)1);

template<class T> void ckmin(T &a, T b) { a = min(a, b); }
template<class T> void ckmax(T &a, T b) { a = max(a, b); }

template<class A, class B> A operator+=(A& l, const B& r) { return l = l+r; }
template<class A, class B> A operator-=(A& l, const B& r) { return l = l-r; }
template<class A, class B> A operator*=(A& l, const B& r) { return l = l*r; }
template<class A, class B> A operator/=(A& l, const B& r) { return l = l/r; }

namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);

    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) { 
        re(first); re(rest...); 
    }

    template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = cd(a,b); }
    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
}

using namespace input;

namespace output {
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);

    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) { 
        pr(first); pr(rest...); 
    }

    template<class T1, class T2> void pr(const pair<T1,T2>& x) { 
        pr("{",x.f,", ",x.s,"}"); 
    }
    template<class T> void prContain(const T& x) {
        pr("{");
        bool fst = 1; trav(a,x) pr(!fst?", ":"",a), fst = 0; 
        pr("}");
    }
    template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
    template<class T> void pr(const vector<T>& x) { prContain(x); }
    template<class T> void pr(const set<T>& x) { prContain(x); }
    template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }
    
    void ps() { pr("\n"); } 
    template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) { 
        pr(first," "); ps(rest...); // print w/ spaces
    }
}

using namespace output;

namespace io {
    void setIn(string s) { freopen(s.c_str(),"r",stdin); }
    void setOut(string s) { freopen(s.c_str(),"w",stdout); }
    void setIO(string s = "") {
        ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
        if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
    }
}

using namespace io;

int N,T,lis[MX];
ll dp[MX];
vi t[MX];
vpi v;
map<int,int> m;

void init() {
    setIO("mowing");
    re(N,T); v.resz(N); re(v); 
    v.pb({0,0}), v.pb({T,T});
    sort(all(v));
    m[0] = 0;
    F0R(i,sz(v)) {
        auto it = m.lb(v[i].s);
        if (i) lis[i] = prev(it)->s+1;
        if (it != m.end()) m.erase(it);
        m[v[i].s] = lis[i]; 
        t[lis[i]].pb(i);
        // ps(m);
    }
    // ps(lis[sz(v)-1]);
    // ps(v);
    // F0R(i,N) ps(lis[i]);
}

vpi st;
int a,b;

ll eval(int a, int b) {
    // assert(v[a].f < v[b].f && v[a].s < v[b].s);
    return dp[a]+(ll)(v[b].f-v[a].f)*(v[b].s-v[a].s);
}

int lst(int x, int y) {
    int l = -1, r = sz(t[b])-1;
    while (l < r) {
        int m = (l+r+1)/2;
        if (eval(x,t[b][m]) <= eval(y,t[b][m])) l = m;
        else r = m-1;
    }
    return l;
}

void insLeft(int x) {
    x = t[a][x];
    while (sz(st)) {
        st.back().f = lst(st.back().s,x);
        if (sz(st) > 1 && st[sz(st)-2].f >= st.back().f) {
            st.pop_back();
        } else break;
    }
    st.pb({MOD,x});
}

void queryLeft(int x) {
    int it = lb(all(st),mp(x,-MOD))-st.begin();
    ckmin(dp[t[b][x]], eval(st[it].s,t[b][x]));
}

void solveLeft(int r, vpi leftBound) {
    st.clear();
    reverse(all(leftBound));
    // stack
    trav(x,leftBound) {
        while (r >= x.f) insLeft(r--);
        queryLeft(x.s);
    }
}

int fst(int x, int y) {
    int l = 0, r = sz(t[b]);
    while (l < r) {
        int m = (l+r)/2;
        if (eval(x,t[b][m]) <= eval(y,t[b][m])) r = m;
        else l = m+1;
    }
    return l;
}

void insRight(int x) {
    x = t[a][x];
    while (sz(st)) {
        st.back().f = fst(st.back().s,x);
        if (sz(st) > 1 && st[sz(st)-2].f <= st.back().f) {
            st.pop_back();
        } else break;
    }
    st.pb({-MOD,x});
}

void queryRight(int x) {
    int lo = 0, hi = sz(st)-1;
    while (lo < hi) {
        int mid = (lo+hi)/2;
        if (st[mid].f <= x) hi = mid;
        else lo = mid+1;
    }
    int it = lo;
    // first one such that <= x 
    ckmin(dp[t[b][x]], eval(st[it].s,t[b][x]));
}

void solveRight(int l, vpi rightBound) {
    st.clear();
    trav(x,rightBound) {
        while (l <= x.f) insRight(l++);
        queryRight(x.s);
    }
}

void deal() {
    /*trav(x,t[i]) pr(v[x]," ");
    ps(); 
    trav(x,t[j]) pr(v[x]," ");
    ps();
    ps(); 
    */
    vpi posi;
    trav(x,t[b]) dp[x] = INF;
    int l = 0, r = -1;
    trav(x,t[b]) {
        while (r+1 < sz(t[a]) && v[t[a][r+1]].f <= v[x].f) r ++;
        while (v[t[a][l]].s > v[x].s) l ++;
        posi.pb({l,r});
        // ps(l,r);
    }

    for (int i = 0; i < sz(posi); ) {
        int I = i;
        vpi leftBound, rightBound;
        while (i < sz(posi) && posi[i].f <= posi[I].s) {
            leftBound.pb({posi[i].f,i});
            rightBound.pb({posi[i].s,i});
            i ++;
        }
        solveLeft(posi[I].s,leftBound);
        solveRight(posi[I].s,rightBound);
    }
}

int main() {
    init();
    // ps(sz(v));
    F0R(i,lis[sz(v)-1]) {
        a = i, b = i+1;
        deal();
    }
    pr(dp[N+1]);
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
