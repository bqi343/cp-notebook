// solves 12~13 test cases

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
const int MX = 100001;
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

template<class T> T invGeneral(T a, T b) {
    a %= b; if (a == 0) return b == 1 ? 0 : -1;
    T x = invGeneral(b,a); 
    return x == -1 ? -1 : ((1-(ll)b*x)/a+b)%b;
}

template<class T> struct modInt {
    T val;
    // T mod = 0;
    static const T mod = MOD;

    void normalize() {
        if (mod == 0) return;
        val %= mod; if (val < 0) val += mod;
    }
    modInt(T v = 0, T m = 0) : val(v) { normalize(); }
    // modInt(T v = 0, T m = 0) : val(v) { normalize(); }

    explicit operator T() const { return val; }
    friend ostream& operator<<(ostream& os, const modInt& a) { return os << a.val; }
    friend bool operator==(const modInt& a, const modInt& b) { return a.val == b.val; }
    friend bool operator!=(const modInt& a, const modInt& b) { return !(a == b); }

    friend void check(modInt& a, modInt& b) { // make sure all operations are valid
        // comment out if mod is static const
        /*if (a.mod > 0 && b.mod > 0) { assert(a.mod == b.mod); return; }
        T mod = max(a.mod,b.mod); if (mod == 0) mod = MOD;
        if (a.mod != mod) { a.mod = mod; a.normalize(); }
        if (b.mod != mod) { b.mod = mod; b.normalize(); }*/
    }
    friend modInt operator+(modInt a, modInt b) {
        check(a,b); a.val += (T)b;
        if (a.val >= a.mod) a.val -= a.mod;
        return a;
    }
    friend modInt operator-(modInt a, modInt b) {
        check(a,b); a.val -= (T)b; 
        if (a.val < 0) a.val += a.mod; 
        return a;
    }
    friend modInt operator-(const modInt& a) { return modInt(0)-a; }

    friend modInt operator*(modInt a, modInt b) {
        check(a,b); a.val = (ll)a.val*(T)b%a.mod; return a;
    }
    friend modInt exp(modInt a, ll p) {
        modInt ans(1,a.mod);
        for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend modInt inv(const modInt& a) {
        return {invGeneral(a.val,a.mod),a.mod};
        // return exp(b,b.mod-2) if prime
    }
    friend modInt operator/(modInt a, modInt b) { 
        check(a,b); return a*inv(b); 
    }
};

typedef modInt<int> mi;
typedef pair<mi,mi> pmi;
typedef vector<mi> vmi;
typedef vector<pmi> vpmi;

int N,K,h[30000][6], v[30000][6];

int hsh(int x, int y) {
    return K*x+y;
}

template<int SZ> struct DSU {
    int par[SZ], sz[SZ];

    DSU() {
        F0R(i,SZ) par[i] = i, sz[i] = 1;
    }

    int get(int x) { // path compression
        if (par[x] != x) par[x] = get(par[x]);
        return par[x];
    }

    bool unite(int x, int y) { // union-by-rank
        x = get(x), y = get(y);
        if (x == y) return 0;
        if (sz[x] < sz[y]) swap(x,y);
        sz[x] += sz[y], par[y] = x;
        return 1;
    }
};

DSU<180000> D;
mi ans(1);
vector<array<int,4>> ed;

void init() {
    setIO("escape"); 
    re(N,K);
    F0R(i,N) F0R(j,K-1) {
        // h[i][j] = rand() % 100+1;
        re(h[i][j]);
        ed.pb({h[i][j],0,i,j});
    }
    F0R(j,K) F0R(i,N-1) {
        // v[i][j] = rand() % 100+1;
        re(v[i][j]);
        ed.pb({v[i][j],1,i,j});
    }
    sort(all(ed));
}


pair<int,mi> operator+(const pair<int,mi>& l, const pair<int,mi>& r) {
    if (l.f != r.f) {
        if (l.f > r.f) return l;
        return r;
    }
    return {l.f,l.s+r.s};
}

vector<pair<vi,pair<int,mi>>> cur, tmp;

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

void unite(vi& a, int x, int y) {
    x = a[x], y = a[y]; if (x == y) return;
    trav(t,a) if (t == y) t = x;
}

void ad(vi a, pair<int,mi> b) {
    tmp.pb({compress(a),b});
}

void swa() {
    sort(all(tmp),[](const pair<vi,pair<int,mi>>& a, const pair<vi,pair<int,mi>>& b) { return a.f < b.f; });
    cur.clear();
    F0R(i,sz(tmp)) {
        if (sz(cur) && cur.back().f == tmp[i].f) cur.back().s += tmp[i].s;
        else cur.pb(tmp[i]);
    }
    tmp.clear();
}

int zz = 0;
vpi cool;

void processRow(int w, int r) {
    F0R(j,K-1) if (h[r][j] == w) {
        tmp = cur;
        trav(t,cur) {
            if (t.f[j] == t.f[j+1]) continue;
            unite(t.f,j,j+1);
            ad(t.f,{t.s.f+1,t.s.s});
        }
        swa();
    }
    ckmax(zz,sz(cur));
}

void processCol(int w, int r) {
    F0R(j,K) {
        trav(t,cur) {
            vi T = t.f; T.pb(MOD);
            F0R(k,K) if (D.get(r*K+j+k) == D.get((r+1)*K+j)) unite(T,k,K);
            auto TT = T; TT.erase(TT.begin()); ad(TT,t.s);
            if (T[0] != T[K] && v[r][j] == w) {
                unite(T,0,K); T.erase(T.begin()); 
                ad(T,{t.s.f+1,t.s.s});
            }
        }
        swa();
    }
}

void adjust(int a, int b) {
    if (a == b) return;
    // ps("??",a,b,ans);
    trav(t,cur) {
        vi T = t.f; 
        // ps("AA",T);
        F0R(i,K) F0R(j,i) if (D.get(K*a+i) == D.get(K*a+j)) unite(T,j,i);
        F0R(i,K) {
            T.pb(K+i);
            F0R(j,K) if (D.get(K*a+j) == D.get(K*b+i)) unite(T,j,K+i);
            F0R(j,i) if (D.get(K*b+j) == D.get(K*b+i)) unite(T,K+j,K+i);
        }
        // ps("BB",T);
        ad(vi(T.begin()+K,T.end()),t.s);
    }
    swa();
}

void tri1(int w) {
    
    int lastRow = 0;
    F0R(i,sz(cool)) {
        if (lastRow != cool[i].f) {
            // ps("??",w,lastRow,cool,i);
            adjust(lastRow,cool[i].f);
        }
        // ps("HA",w,i,cool[i]);
        if (cool[i].s == 1) {
            processCol(w,cool[i].f);
            lastRow = cool[i].f+1;
        } else {
            processRow(w,cool[i].f);
            lastRow = cool[i].f;
        }
        // unite lastRow to cool[i].f 
    }
}

void tri0(int w) {
    F0R(i,N) {
        processRow(w,i);
        if (i != N-1) processCol(w,i);
    }
}

void process(int w) {
    sort(all(cool)); cool.erase(unique(all(cool)),cool.end());
    
    cur.clear(), tmp.clear();
    vi a(K); F0R(i,K) a[i] = D.get(hsh(0,i));
    cur.pb({compress(a),{0,1}});
    
    tri1(w);
    // tri0(w);
    
    pair<int,mi> res = {0,0};
    trav(t,cur) res += t.s;
    ans *= res.s;
    // ps(ans,w,cool);
}

int main() {
    init();
    for (int i = 0; i < sz(ed); ) {
        int I = i;
        while (i < sz(ed) && ed[i][0] == ed[I][0]) {
            cool.pb({ed[i][2],ed[i][1]});
            i ++;
        }
        process(ed[I][0]); cool.clear();
        FOR(j,I,i) {
            if (ed[j][1] == 0) {
                D.unite(hsh(ed[j][2],ed[j][3]),hsh(ed[j][2],ed[j][3]+1));
            } else {
                D.unite(hsh(ed[j][2],ed[j][3]),hsh(ed[j][2]+1,ed[j][3]));
            }
        }
        // ps(ans);
    }
    // ps(zz);
    cout << ans;
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/