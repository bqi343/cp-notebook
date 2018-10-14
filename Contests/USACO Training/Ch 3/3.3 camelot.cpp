/*
ID: bqi3431
PROG: camelot
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

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100001;

namespace io {
    template<typename Test, template<typename...> class Ref>
    struct is_specialization : std::false_type {};

    template<template<typename...> class Ref, typename... Args>
    struct is_specialization<Ref<Args...>, Ref>: std::true_type {};
    // https://stackoverflow.com/questions/16337610/how-to-know-if-a-type-is-a-specialization-of-stdvector

    void setIn(string s) { freopen(s.c_str(),"r",stdin); }
    void setOut(string s) { freopen(s.c_str(),"w",stdout); }
    void setIO(string s = "") {
        ios_base::sync_with_stdio(0); cin.tie(0);
        if (sz(s)) { setIn(s+".in"), setOut(s+".out"); }
    }
    
    // INPUT 
    
    // double input seems slow on CF
    void re(double& x) { string t; cin >> t; x = stod(t); } 
    void re(ld& x) { string t; cin >> t; x = stold(t); }
    template<class T> void re(T& x) { cin >> x; }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) { 
        re(first); re(rest...); 
    }
    template<class T1, class T2> istream& operator>>(istream& is, pair<T1,T2>& p) {
        is >> p.f >> p.s; return is;
    }
    template<class T> istream& operator>>(istream& is, vector<T>& a) {
        F0R(i,sz(a)) is >> a[i];
        return is;
    }
    
    // OUTPUT 
    
    template<class T> void pr(const T& x) { cout << x << '\n'; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) { 
        cout << first << ' '; pr(rest...); 
    }
    template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) {
        os << '{' << a.f << ", " << a.s << '}'; return os;
    }
    template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
        os << '{';
        F0R(i,sz(a)) {
            if (i) {
                os << ", ";
                if (is_specialization<T, vector>::value) os << '\n';
            }
            os << a[i];
        }
        os << '}';
        return os;
    }
}

using namespace io;

template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;

template<class T> T poll(queue<T>& x) {
    T y = x.front(); x.pop();
    return y;
}

vpi adj[780];

void addEdge(int A, int B, int C) {
    adj[A].pb({B,C}), adj[B].pb({A,C});
}

int R,C;
pi king;
int xd[8] = {2,1,-1,-2,-2,-1,1,2};
int yd[8] = {1,2,2,1,-1,-2,-2,-1};

int ans = MOD;
    
template<int SZ> struct Dijkstra {
    int dist[SZ];
    
    Dijkstra() {
        F0R(i,SZ) dist[i] = MOD;
    }
    
    void gen(int st) {
        queue<pi> q; q.push({dist[st] = 0,st});
        while (sz(q)) {
            auto x = poll(q);
            if (dist[x.s] < x.f) continue;
            for (auto y: adj[x.s]) if (x.f+y.s < dist[y.f]) 
                q.push({dist[y.f] = x.f+y.s,y.f});
        }
    }
    
    void gen() {
        priority_queue<pi,vpi,greater<pi>> q; 
        F0R(i,R*C) q.push({dist[i],i});
        while (sz(q)) {
            auto x = q.top(); q.pop();
            if (dist[x.s] < x.f) continue;
            for (auto y: adj[x.s]) if (x.f+y.s < dist[y.f]) 
                q.push({dist[y.f] = x.f+y.s,y.f});
        }
    }
};

Dijkstra<780> D[780], E[780];

vi knight; 

void test(int a, int b) {
    int tot = max(abs(king.f-a),abs(king.s-b)), save = 0;
    
    for (int t: knight) {
        tot += D[C*a+b].dist[t];
        if (tot >= MOD) return;
        save = min(save,E[t].dist[C*a+b]-max(abs(king.f-a),abs(king.s-b))-D[C*a+b].dist[t]);
    }
    
    ans = min(ans,tot+save);
}

int main() {
    setIO("camelot");
    re(R,C); swap(R,C);
    char a; int b; re(a,b);
    king = {a-'A',b-1};
    
    while (cin >> a >> b) knight.pb(C*(a-'A')+b-1);
    F0R(i,R) F0R(j,C) {
        F0R(k,4) {
            int I = i+xd[k], J = j+yd[k];
            if (0 <= I && I < R && 0 <= J && J < C) {
                addEdge(C*i+j,C*I+J,1);
            }
        }
    }
    F0R(i,R*C) {
        D[i].gen(i);
        F0R(j,R) F0R(k,C) E[i].dist[C*j+k] = D[i].dist[C*j+k]+max(abs(j-king.f),abs(k-king.s));
        E[i].gen();
    }
    F0R(i,R) F0R(j,C) test(i,j);
    cout << ans << "\n";
}

/* 
* (Actually read this pls)
    * Rlly bad errors: int overflow, array bounds
    * Less bad errors: special cases (n=1?), set tle
    * Common sense: do smth instead of nothing
*/
