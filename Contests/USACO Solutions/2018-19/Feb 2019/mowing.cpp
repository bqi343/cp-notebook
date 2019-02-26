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
    
    template<class Arg> void ps(const Arg& first) { pr(first,"\n"); } // print w/ spaces
    template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) { 
        pr(first," "); ps(rest...); 
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

namespace modOp {
    int ad(int a, int b, int mod = MOD) { return (a+b)%mod; }
    int sub(int a, int b, int mod = MOD) { return (a-b+mod)%mod; }
    int mul(int a, int b, int mod = MOD) { return (ll)a*b%mod; }
    
    int AD(int& a, int b, int mod = MOD) { return a = ad(a,b,mod); }
    int SUB(int& a, int b, int mod = MOD) { return a = sub(a,b,mod); }
    int MUL(int& a, int b, int mod = MOD) { return a = mul(a,b,mod); }
    
    int po (int b, int p, int mod = MOD) { return !p?1:mul(po(mul(b,b,mod),p/2,mod),p&1?b:1,mod); }
    int inv (int b, int mod = MOD) { return po(b,mod-2,mod); }
    
    int invGeneral(int a, int b) { // 0 < a < b, gcd(a,b) = 1
        if (a == 0) return b == 1 ? 0 : -1;
        int x = invGeneral(b%a,a); 
        return x == -1 ? -1 : ((1-(ll)b*x)/a+b)%b;
    }
}

using namespace modOp;

int N,T;
ll ans[MX];
map<int,int> m;
vpi f;
vi res[MX];
// set with y-coordinate, #, x-coordinate, ans

void init() {
    setIO("mowing"); 
    re(N,T); f.resz(N); re(f);
    f.pb({0,0}), f.pb({T,T}); sort(all(f));
    F0R(i,sz(f)) {
        int num = -1;
        if (sz(m)) num = prev(m.lb(f[i].s))->s;
        num ++;
        m[f[i].s] = num; auto it = m.find(f[i].s);
        if (next(it) != m.end()) m.erase(next(it));
        res[num].pb(i);
    }
    // ps(m);
}

vi seg[1<<19];
vpi SEG[1<<19];
vi er;
bool ER[1<<19];

void ins(int ind, int lo, int hi, int l, int r, int x) {
    if (lo > hi || lo > r || hi < l) return;
    if (lo <= l && r <= hi) {
        seg[ind].pb(x);
        if (!ER[ind]) {
            ER[ind] = 1;
            er.pb(ind);
        }
        return;
    }
    int m = (l+r)/2;
    ins(2*ind,lo,hi,l,m,x);
    ins(2*ind+1,lo,hi,m+1,r,x);
}

ll eval(int a, int b) {
    return ans[a]+(ll)(f[b].f-f[a].f)*(f[b].s-f[a].s);
}

int fst(int x, int y, vi& b) {
    if (x == -1) return 0;
    if (x<y) {
        ps("WHAT",x,y);
        exit(0);
    }
    int lo = 0, hi = sz(b);
    while (lo < hi) {
        int mid = (lo+hi)/2;
        if (eval(y,b[mid]) < eval(x,b[mid])) hi = mid;
        else lo = mid+1;
    }
    return lo;
}

void gen(int ind, vi& b) {
    assert(sz(seg[ind]));
    reverse(all(seg[ind]));
    // ps(seg[ind]);
    vi tmp;
    trav(i,seg[ind]) {
        while (sz(tmp) && fst(sz(tmp) == 1 ? -1 : tmp[sz(tmp)-2],tmp[sz(tmp)-1],b) >= fst(tmp[sz(tmp)-1],i,b)) tmp.pop_back();
        tmp.pb(i);
    }
    F0R(i,sz(tmp)) {
        SEG[ind].pb({fst(i == 0 ? -1 : tmp[i-1],tmp[i],b),tmp[i]});
    }
}

vi z = {2,4};

ll query(int x, vi& b, int ind, int l, int r) {
    ll res = INF;
    if (sz(seg[ind])) {
        auto it = prev(lb(all(SEG[ind]),mp(x,MOD)));
        // if (b == z && x == 1) ps("??",SEG[ind],it->s);
        ckmin(res,eval(it->s,b[x]));
    }
    // if (b == z && x == 1) ps("WHAT",x,b[x],l,r,res,seg[ind],SEG[ind],eval(SEG[ind].back().s,4));
    if (l != r) {
        int m = (l+r)/2;
        if (x <= m) ckmin(res,query(x,b,2*ind,l,m));
        else ckmin(res,query(x,b,2*ind+1,m+1,r));
    }
    return res;
}

void deal(vi a, vi b) {
    int l = 0, r = -1;
    F0R(i,sz(a)) {
        while (l < sz(b) && f[b[l]].f < f[a[i]].f) l ++;
        while (r < sz(b)-1 && f[b[r+1]].s > f[a[i]].s) r ++;
        // ps(a,b,i,l,r);
        ins(1,l,r,0,sz(b)-1,a[i]);
    }
    // generate the binsearch things for each segment
    trav(i,er) gen(i,b);
    F0R(i,sz(b)) {
        ans[b[i]] = query(i,b,1,0,sz(b)-1);
        // ps(b[i],f[b[i]],ans[b[i]]);
    }
    trav(i,er) {
        ER[i] = 0;
        seg[i].clear();
        SEG[i].clear();
    }
    er.clear();
}

int main() {
    // you should actually read the stuff at the bottom
    init();
    // ps(eval(0,5));
    FOR(i,1,MX) if (sz(res[i])) deal(res[i-1],res[i]);
    pr(ans[sz(f)-1]);
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/