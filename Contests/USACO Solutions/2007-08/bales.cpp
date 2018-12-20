/*
 ID: bqi3431
 PROG: bales
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

int N,Q;
vector<array<int,3>> v;
map<int,int> bad;

void checkValid() {
    auto a = vpi(all(bad));
    F0R(i,sz(a)) if (a[i].f > a[i].s) exit(5);
    F0R(i,sz(a)-1) if (a[i].s >= a[i+1].f-1) exit(5);
}

bool oc[10001];

void process(int x, int y) {
    checkValid();
    //pr("HI",x,y);
    while (1) {
        auto it = bad.lb(x);
        if (it == bad.end() || it->f > y) break;
        if (it->s > y) ckmax(bad[y+1],it->s);
        bad.erase(it);
    }
    auto it = bad.lb(x);
    if (it != bad.begin()) {
        int t = prev(it)->s;
        ckmin(prev(it)->s,x-1);
        if (t > y) bad[y+1] = t;
    }
    pi range = {x,y};
    bad[x] = y; it = bad.find(x);
    if (it != bad.begin() && prev(it)->s == x-1) {
        range.f = prev(it)->f;
        bad.erase(prev(it));
    }
    if (next(it) != bad.end() && next(it)->f == y+1) {
        range.s = next(it)->s;
        bad.erase(next(it));
    }
    bad.erase(it); bad[range.f] = range.s;
    /*trav(z,bad) cout << z << " | ";
    pr("");*/
}

bool ok(int mx) {
    bad.clear();
    // F0R(i,10001) oc[i] = 0;
    vector<array<int,3>> V;
    F0R(i,mx) V.pb(v[i]);
    sort(V.rbegin(),V.rend());
    for (int i = 0; i < sz(V); ) {
        int I = i;
        pi inter = {-MOD,MOD};
        while (i < sz(V) && V[i][0] == V[I][0]) {
            ckmax(inter.f,V[i][1]); ckmin(inter.s,V[i][2]);
            i ++;
        }
        /*cout << V[i][0] << " " << inter.f << " " << inter.s << "\n";
        bool contain = 0;
        FOR(i,inter.f,inter.s+1) if (!oc[i]) contain = 1;
        if (!contain) {
            cout << "?? " << inter << "\n"; 
            
            trav(z,bad) cout << z << " | ";
            exit(0);
            return 0;
        }*/
        if (inter.f > inter.s) return 0;
        auto it = bad.ub(inter.f);
        if (it != bad.begin() && prev(it)->s >= inter.s) return 0;
        FOR(j,I,i) process(V[j][1],V[j][2]);
    }
    return 1;
}

int main() {
    // you should actually read the stuff at the bottom
    setIO("bales"); 
    re(N,Q);
    F0R(i,Q) {
        int L,R,A; re(L,R,A);
        v.pb({A,L,R});
    }
    // cout << "WHAT " << ok(55); exit(0);
    // ok(4); exit(0);
    int lo = 0, hi = Q;
    while (lo < hi) {
        int mid = (lo+hi+1)/2;
        if (ok(mid)) lo = mid;
        else hi = mid-1;
    }
    if (lo == Q) pr(0);
    else pr(lo+1);
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
