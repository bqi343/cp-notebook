/*
 ID: bqi3431
 PROG: alake
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

int N,H[MX],W[MX], w[MX];
int child[MX][2], par[MX],leftmost[MX], rightmost[MX];
ll ans[MX], ti;
map<pi,int> m;

ll getPar(int x) {
    if (H[par[x]] < H[x]) {
        cout << "OOPS " << x << "\n";
    }
    return (ll)w[x]*(H[par[x]]-H[x]);
}

void fromRight(int x, int p) {
    if (!x || x == p) return;
    fromRight(rightmost[child[x][0]],x);
    ans[x] = ti+w[x];
    ti += getPar(x);
    fromRight(par[x],p);
    /*fromLeft(child[x][1]);
    fromRight(child[x][0]);
    ans[x] = ti+w[x];
    pr("R",x,ans[x]);
    ti += getPar(x);*/
}

void fromLeft(int x, int p) {
    if (!x || x == p) return;
    // cout << "L " << x << " " << p << "\n";
    // if (x == 43) cout << "HUH " << x << " " << p << "\n";
    fromLeft(leftmost[child[x][1]],x);
    ans[x] = ti+w[x];
    ti += getPar(x);
    fromLeft(par[x],p);
    /*fromRight(child[x][0]);
    fromLeft(child[x][1]);
    pr("L",x,ans[x]);*/
}

int main() {
    // you should actually read the stuff at the bottom
    setIO("alake"); 
    re(N);
    FOR(i,1,N+1) {
        re(W[i],H[i]);
        w[i] = W[i];
    }
    vi z; FOR(i,1,N+1) z.pb(i); sort(all(z),[](int a, int b) { return H[a] < H[b]; }); 
    // pr(z); exit(0);
    trav(x,z) {
        pi range = {x,x};
        m[range] = x; auto it = m.find(range);
        if (next(it) != m.end() && next(it)->f.f == x+1) {
            range.s = next(it)->f.s;
            par[next(it)->s] = x;
            child[x][1] = next(it)->s;
            w[x] += w[child[x][1]];
            m.erase(next(it));
        }
        if (it != m.begin() && prev(it)->f.s == x-1) {
            range.f = prev(it)->f.f;
            par[prev(it)->s] = x;
            child[x][0] = prev(it)->s;
            w[x] += w[child[x][0]];
            m.erase(prev(it));
        }
        leftmost[x] = range.f;
        rightmost[x] = range.s;
        // pr(x,range.f,range.s);
        m.erase(it); m[range] = x;
    }
    // pr(child[13][0],child[13][1]);
    // cout << z << " " << w[z.back()] << " " << N << "\n";
    // pr(w[2]); exit(0);
    // FOR(i,1,N+1) pr(i,child[i][0],child[i][1],par[i]);
    int cur = z[0];
    while (1) {
        ans[cur] = ti+w[cur];
        // cout << "AH " << cur << "\n";
        if (par[cur] == 0) break;
        ti += getPar(cur);
        if (child[par[cur]][0] == cur) {
            fromLeft(leftmost[child[par[cur]][1]],par[cur]);
        } else {
            assert(child[par[cur]][1] == cur);
            fromRight(rightmost[child[par[cur]][0]],par[cur]);
        }
        cur = par[cur];
    }
    FOR(i,1,N+1) pr(ans[i]);
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
