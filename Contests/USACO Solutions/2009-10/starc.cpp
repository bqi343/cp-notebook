/*
 ID: bqi3431
 PROG: starc
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

int N,M;
vcd poly = {cd(100,(ld)0.01),cd(100,100),cd((ld)0.01,100),cd((ld)0.01,(ld)0.01)}; // ccw 

char win(vi v) {
    int ans = 0;
    trav(x,poly) {
        ld z = v[0]*x.real()+v[1]*x.imag()+v[2];
        if (z >= -(1e-10)) ans |= 1;
        if (z <= (1e-10)) ans |= 2;
    }
    if (ans == 1) return 'J';
    if (ans == 2) return 'B';
    return 'U';
}

ld eval(vi v, cd a) {
    return v[0]*a.real()+v[1]*a.imag()+v[2];
}

cd intersect(cd a, cd b, vi v) {
    return (eval(v,a)*b-eval(v,b)*a)/(eval(v,a)-eval(v,b));
}

void cut(vi v) {
    vcd POLY;
    F0R(i,sz(poly)) {
        int j = (i+1)%sz(poly);
        if (eval(v,poly[i]) > 0 && eval(v,poly[j]) < 0) {
            POLY.pb(intersect(poly[i],poly[j],v));
        }
        if (eval(v,poly[i]) < 0 && eval(v,poly[j]) > 0) {
            POLY.pb(intersect(poly[i],poly[j],v));
        }
        if (eval(v,poly[j]) >= 0) POLY.pb(poly[j]);
    }
    swap(poly,POLY);
}

void initPoly() {
    setIO("starc"); 
    re(N,M);
    cut({100,-1,0});
    cut({-1,100,0});
    F0R(i,N) {
        char w; vi A(3), B(3); re(w,A,B); F0R(i,3) A[i] -= B[i];
        if (w == 'B') F0R(i,3) A[i] *= -1; // A[0]*S1+A[1]*S2+A[2] >= 0 
        cut(A);
    }
    // pr(poly);
}

int main() {
    // you should actually read the stuff at the bottom
    initPoly();
    F0R(i,M) {
        vi A(3), B(3); re(A,B); F0R(i,3) A[i] -= B[i];
        /*if (i == 1719) {
            cout << A << " " << win(A);
            trav(a,poly) pr(eval(A,a));
            exit(0);
        }*/
        pr(win(A));
    }
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
