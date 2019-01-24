/*
ID: bqi3431
PROG: treasure
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

const int tmp = (chrono::high_resolution_clock::now().time_since_epoch().count()%(MOD-1)+(MOD-1))%(MOD-1)+1;

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
    template<class T, size_t SZ> ostream& operator<<(ostream& os, const array<T,SZ>& a) {
        return printArray(os,a,SZ);
    }
    template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
        return printArray(os,a,sz(a));
    }
    template<class T> ostream& operator<<(ostream& os, const set<T>& a) {
        os << vector<T>(all(a)); return os;
    }
    template<class T1, class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {
        os << vector<pair<T1,T2>>(all(a)); return os;
    }
    
    template<class T> void pr(const T& x) { cout << x << '\n'; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) { 
        cout << first << ' '; pr(rest...); 
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

namespace pairOp {
    template<class T> T operator+=(T& l, const T& r) { return l = l+r; }
    template<class T> T operator-=(T& l, const T& r) { return l = l-r; }
    template<class T> T operator*=(T& l, const T& r) { return l = l*r; }

    pi operator+(const pi& l, const pi& r) { return {ad(l.f,r.f),ad(l.s,r.s)}; }
    pi operator-(const pi& l, const pi& r) { return {sub(l.f,r.f),sub(l.s,r.s)}; }
    pi operator*(const pi& l, const pi& r) { return {mul(l.f,r.f),mul(l.s,r.s)}; }
    pi operator*(const pi& l, const int& r) { return l*pi(r,r); }
    pi operator*(const int& r, const pi& l) { return l*r; }
    pi operator*=(pi& l, const int& r) { return l = l*r; }
}

using namespace pairOp;


struct hsh {
    vpi S;
    vpi pows, ipows, cum;
    pi base = mp(948392576,tmp), invbase; // probably want to randomize base
    
    hsh() {}
    
    void gen(vector<uint64_t>& v) {
        S.resz(sz(v));
        invbase = {inv(base.f),inv(base.s)};
        pows.resize(sz(S)), ipows.resize(sz(S)), cum.resize(sz(S)+1);
        
        pows[0] = ipows[0] = {1,1};
        FOR(i,1,sz(S)) pows[i] = pows[i-1]*base, ipows[i] = ipows[i-1]*invbase;
        F0R(i,sz(S)) {
            S[i] = {v[i]%MOD,v[i]/MOD%MOD};
            // pr(v[i]%MOD,v[i]/MOD%MOD);
            cum[i+1] = cum[i]+pows[i]*S[i];
        }
    }
    
    pi get(int l, int r) {  
        // if (l < 0 || r >= sz(S)) pr("OOPS",l,r);
        return ipows[l]*(cum[r+1]-cum[l]); 
    }
    
    int lcp(hsh& b) {
        int lo = 0, hi = min(sz(S),sz(b.S));
        while (lo < hi) {
            int mid = (lo+hi+1)/2;
            if (cum[mid] == b.cum[mid]) lo = mid;
            else hi = mid-1;
        }
        return lo;
    }
};

hsh leftHsh, rightHsh;

int N, depth[MX], par[MX], comp[MX], pos[MX];
vi adj[MX], cyc;
bool inCyc[MX];
pi points;
uint64_t subtreeHash[MX];
set<pair<uint64_t,pi>> res;

uint64_t comb(uint64_t h, uint64_t k) { // https://www.boost.org/doc/libs/1_68_0/boost/container_hash/hash.hpp
    const uint64_t m = UINT64_C(0xc6a4a7935bd1e995);
    const int r = 47;

    k *= m;
    k ^= k >> r;
    k *= m;

    h ^= k;
    h *= m;

    // Completely arbitrary number, to prevent 0's
    // from hashing to 0.
    h += 0xe6546b64;
    return h;
}

uint64_t hsh(vector<uint64_t> x) {
    sort(all(x));
    uint64_t s = 0;
    trav(y,x) s = comb(s,y);
    return s;
}

pi getHash(int cpos) {
    return min(leftHsh.get(cpos+1,cpos+sz(cyc)-1),rightHsh.get(2*sz(cyc)-1-(cpos+sz(cyc)-1),2*sz(cyc)-1-(cpos+1)));
}

void genHash(int x, int y) {
    vector<uint64_t> v = {0};
    for (int i: adj[x]) if (i != y && !inCyc[i]) {
        comp[i] = comp[x]; genHash(i,x);
        v.pb(subtreeHash[i]);
    }
    subtreeHash[x] = hsh(v);
}

void propHash(int x, int y) {
    for (int i: adj[x]) if (i != y && !inCyc[i]) {
        subtreeHash[i] = comb(subtreeHash[i],subtreeHash[x]);
        propHash(i,x);
    }
}

void dfs(int x) {
    depth[x] = depth[par[x]]+1;
    for (int y: adj[x]) {
        if (depth[y] == 0) {
            par[y] = x; dfs(y);
        } else if (depth[y] < depth[x] && y != par[x]) points = {x,y};
    }
}

int main() {
    // you should actually read the stuff at the bottom
    setIO("treasure"); 
    re(N);
    F0R(i,N) {
        int a,b; re(a,b);
        adj[a].pb(b), adj[b].pb(a);
    }
    dfs(1);
    // pr(points); exit(0);
    while (points.f != points.s) {
        cyc.pb(points.f);
        points.f = par[points.f];
    }
    cyc.pb(points.f); for (int i: cyc) inCyc[i] = 1;
    int co = 0;
    for (int i: cyc) {
        comp[i] = i;
        pos[i] = co++;
        genHash(i,0);
    }
    for (int i: cyc) propHash(i,0);
    
    // pr(cyc);
    vector<uint64_t> z; for (int i: cyc) z.pb(subtreeHash[i]);
    z.insert(z.end(),all(z)); leftHsh.gen(z);
    reverse(all(z)); rightHsh.gen(z);
    // exit(0);
    FOR(i,1,N+1) if (sz(adj[i]) < 4) {
        res.insert({subtreeHash[i],getHash(pos[comp[i]])});
        // pr(i,comp[i],subtreeHash[i],getHash(pos[comp[i]]));
    }
    pr(sz(res));
    // FOR(i,1,N+1) pr(i,comp[i],subtreeHash[i],);
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
