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
const ll INF = 2e18;
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

int N, ans;
ll K;
vi cow;

/*bool inc(vi c) {
    FOR(i,1,sz(c)) if (c[i] < c[i-1]) return 0;
    return 1;
}

void brute() {
    pair<int,vector<vi>> bes = {MOD,{}};
    F0R(i,1<<N) {
        vi c = cow;
        vi ret;
        F0R(j,N) if (i&(1<<j)) {
            c.erase(find(all(c),j+1));
            ret.pb(j+1);
        }
        if (inc(c)) {
            if (sz(ret) < bes.f) {
                bes.f = sz(ret);
                bes.s.clear();
            }
            if (sz(ret) == bes.f) bes.s.pb(ret);
        }
    }
    pr(bes.f);
    trav(x,bes.s[K-1]) pr(x);
}*/

void AD(ll& a, ll b) {
    a = min(a+b,INF);
}

// LIS template

vi bes = {INT_MAX}; // last term of increasing sequence with i terms
vpi tmp[MX];
vl dp[MX];

void ad(int i, int x) { // add terms of sequence one by one
    // sz(bes)-1 is your current answer
    int lo = 0, hi = sz(bes)-1;
    while (lo < hi) {
        int mid = (lo+hi+1)/2;
        if (bes[mid] > x) lo = mid;
        else hi = mid-1;
    }
    lo ++;
    if (lo == sz(bes)) bes.pb(0);
    bes[lo] = x; tmp[lo].pb({i,x}); dp[lo].pb(0);
    F0R(i,sz(tmp[lo-1])) if (tmp[lo].back().s < tmp[lo-1][i].s) AD(dp[lo].back(),dp[lo-1][i]);
    // this is actually O(N^2) in worst case, but can be reduced to O(NlogN)
}

bool ok[MX];

int main() {
    // you should actually read the stuff at the bottom
    setIO("itout"); 
    re(N,K); cow.resz(N); re(cow);
    
    tmp[0] = {{MOD,INT_MAX}}; dp[0] = {1};
    F0Rd(i,N) ad(i,cow[i]);
    vpi ret;
    FORd(i,1,sz(bes)) { // instead of finding K-th smallest anti-LIS, find K-th greatest LIS
        F0Rd(j,sz(dp[i])) {
            if (sz(ret) && (ret.back().f > tmp[i][j].f || ret.back().s > tmp[i][j].s)) continue;
            if (dp[i][j] < K) K -= dp[i][j];
            else {
                ret.pb(tmp[i][j]);
                break;
            }
        }
    }
    trav(x,ret) ok[x.s] = 1;
    pr(N-sz(ret));
    FOR(i,1,N+1) if (!ok[i]) pr(i);
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/