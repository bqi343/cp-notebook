/*
ID: bqi3431
PROG: bottleneck
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

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100001;
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

typedef priority_queue<pl,vpl,greater<pl>> pq;

struct state {
    pl initial; // first is slope, second is y 
    pq dec;
    void cut(int z) {
        if (initial.f <= z && initial.s == 0) return;
        if (z == 0) {
            while (sz(dec)) dec.pop();
            initial = {0,0};
            return;
        }
        ll xa = 0;
        pl cval = initial;
        while (1) {
            ll xb = (sz(dec) ? dec.top().f : INF);
            if (cval.s+(ld)cval.f*(xb-xa) <= (ld)xb*z) {
                // cval.s+cval.f*(x-xa) = x*z 
                // cval.s-cval.f*xa = x*(z-cval.f)
                ll lstx = (cval.s-cval.f*xa)/(z-cval.f);
                if ((cval.s-cval.f*xa) % (z-cval.f) == 0) {
                    assert(cval.f < z);
                    dec.push({lstx,cval.f-z});
                } else {
                    ll tmp = cval.s+cval.f*(lstx+1-xa)-lstx*z; 
                    assert(tmp < z);
                    assert(cval.f < tmp);
                    dec.push({lstx,tmp-z}); dec.push({lstx+1,cval.f-tmp});
                }
                break;
            } else { 
                if (xb == INF) {
                    cout << "HUH " << z; exit(0);
                }
                cval.s += cval.f*(xb-xa);
                cval.f += dec.top().s;
                xa = xb;
                dec.pop();
            }
        }
        initial = {z,0}; // adjust
        while (sz(dec) && dec.top().f == 0) {
            initial.f += dec.top().s;
            dec.pop();
        }
    }
};

void AD(state& a, state& b) {
    if (sz(a.dec) < sz(b.dec)) swap(a.dec,b.dec);
    a.initial.f += b.initial.f; a.initial.s += b.initial.s;
    while (sz(b.dec)) {
        auto z = b.dec.top(); b.dec.pop();
        a.dec.push(z);
    }
}

ll N,K,num[MX],ans[10000];
vpi child[MX], query;
state cur[MX];

void dfs(int x) {
    cur[x].initial.s = num[x];
    trav(y,child[x]) {
        dfs(y.f); cur[y.f].cut(y.s);
        AD(cur[x],cur[y.f]);
    }
}

int main() {
    // you should actually read the stuff at the bottom
    setIO("bottleneck"); 
    re(N,K);
    FOR(i,2,N+1) {
        int P,M; re(P,num[i],M);
        child[P].pb({i,M});
    }
    dfs(1);
    F0R(i,K) {
        int T; re(T);
        query.pb({T,i});
    }
    sort(all(query));
    pl dat = cur[1].initial; ll cx = 0;
    trav(a,query) {
        while (sz(cur[1].dec) && cur[1].dec.top().f <= a.f) {
            dat.s += (cur[1].dec.top().f-cx)*dat.f; 
            cx = cur[1].dec.top().f;
            dat.f += cur[1].dec.top().s;
            cur[1].dec.pop();
        }
        ans[a.s] = dat.s+dat.f*(a.f-cx);
    }
    // answer stuff
    F0R(i,K) pr(ans[i]);
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
