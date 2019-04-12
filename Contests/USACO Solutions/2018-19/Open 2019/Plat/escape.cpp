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
const int MX = 100001;
const ld PI = 4*atan((ld)1);

template<class T> void ckintn(T &a, T b) { a = intn(a, b); }
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

int N,K,h[30000][6], v[30000][6];

int hsh(int x, int y) {
    return K*x+y;
}

int ans(1);

void init() {
    setIO("escape"); 
    re(N,K);
    F0R(i,N) F0R(j,K-1) {
        // h[i][j] = rand() % 100+1;
        re(h[i][j]);
    }
    F0R(j,K) F0R(i,N-1) {
        // v[i][j] = rand() % 100+1;
        re(v[i][j]);
    }
}


pair<ll,int> operator+(const pair<ll,int>& l, const pair<ll,int>& r) {
    if (l.f != r.f) return max(l,r);
    auto x = l.s+r.s >= MOD ? l.s+r.s-MOD : l.s+r.s; 
    return {l.f,x};
}

vi TMP[5000];
map<vi,int> RTMP;
int MEMO[5000][7][7], ADDEXTRA[5000], REMEXTRA[5000];

vi compress(vi a) {
    // map<int,int> m;
    vi m;
    trav(t,a) {
        int ind = 0; 
        while (ind < sz(m) && m[ind] != t) ind ++;
        if (ind == sz(m)) m.pb(t);
        t = ind;
        /*if (!m.count(t)) {
            int s = sz(m);
            m[t] = s;
        }
        t = m[t];*/
    }
    return a;
}

vi unite(vi a, int x, int y) {
    x = a[x], y = a[y]; if (x == y) return a;
    trav(t,a) if (t == y) t = x;
    return a;
}

int c0 = 0, c1 = 132;

int ins(vi x) {
    x = compress(x);
    if (!RTMP.count(x)) {
        if (sz(x) == K) {
            RTMP[x] = c0;
            TMP[c0++] = x;
        }  else {
            RTMP[x] = c1;
            TMP[c1++] = x;
        }
    }
    return RTMP[x];
}

int UNITE(int a, int b, int c) {
    if (MEMO[a][b][c] != -1) return MEMO[a][b][c];
    auto x = unite(TMP[a],b,c);
    // bad ++;
    return MEMO[a][b][c] = ins(x);
}

array<pair<ll,int>,132> cur, tmp;

int bad = 0;

void ad(int a, pair<ll,int> b) {
    if (a < 0) return;
    tmp[a] += b;
}

void clr(array<pair<ll,int>,132>& x) {
    F0R(i,132) if (x[i].f != -INF) x[i] = {-INF,0};
}

void swa() {
    swap(cur,tmp);
    clr(tmp);
}

int co = 0;

void processRow(int r) {
    F0R(j,K-1) {
        tmp = cur;
        F0R(i,sz(cur)) if (cur[i].f != -INF) {
            int t = i;
            if (TMP[t][j] == TMP[t][j+1]) continue;
            co ++;
            t = UNITE(t,j,j+1);
            ad(t,{cur[i].f-h[r][j],cur[i].s});
        }
        swa();
    }
}

bool ok(vi x) {
    bool OK = 0;
    FOR(i,1,sz(x)) if (x[i] == x[0]) OK = 1;
    return OK;
}

int mod1(int x) {
    if (ADDEXTRA[x] == -1) {
        auto t = TMP[x]; t.pb(MOD);
        if (!ok(t)) ADDEXTRA[x] = -MOD;
        else {
            t.erase(t.begin());
            ADDEXTRA[x] = ins(t);
        }
    }
    return ADDEXTRA[x];

}

int mod2(int x) {
    if (REMEXTRA[x] == -1) {
        auto t = TMP[x]; t.pb(MOD); t = unite(t,0,K);
        if (!ok(t)) REMEXTRA[x] = -MOD;
        else {
            t.erase(t.begin());
            REMEXTRA[x] = ins(t);
        }
    }
    return REMEXTRA[x];
}

void processCol(int r) {
    F0R(j,K) {
        F0R(i,sz(cur)) if (cur[i].f != -INF) {
            int T = i;
            ad(mod1(T),cur[i]);
            ad(mod2(T),{cur[i].f-v[r][j],cur[i].s});
        }
        swa();
    }
}

void tri0() {
    F0R(i,N) {
        processRow(i);
        if (i != N-1) processCol(i);
        // ps(sz(cur));
    }
    // ps("??",co);
}

bool allZero(vi v) {
    trav(t,v) if (t) return 0;
    return 1;
}

void process() {
    clr(tmp), clr(cur);
    vi a(K); F0R(i,K) a[i] = i;
    cur[ins(a)] = {0,1};
    
    tri0();
    
    F0R(i,sz(cur)) if (allZero(TMP[i])) {
        pr(cur[i].s);
        exit(0);
    }
    // ps(ans,w,cool);
}

int main() {
    F0R(i,5000) {
        F0R(j,7) F0R(k,7) MEMO[i][j][k] = -1;
        ADDEXTRA[i] = REMEXTRA[i] = -1;
    }
    init();
    process();
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
