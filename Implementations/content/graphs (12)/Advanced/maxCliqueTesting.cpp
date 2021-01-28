#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; 
typedef string str; 

typedef pair<int,int> pi;
typedef pair<ll,ll> pl; 
typedef pair<ld,ld> pd; 

typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef vector<ld> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 

#define mp make_pair 
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() 
#define rsz resize
#define ins insert 
#define ft front() 
#define bk back()
#define pf push_front 
#define pb push_back
#define eb emplace_back 
#define lb lower_bound 
#define ub upper_bound 

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5; 
const ll INF = 1e18; 
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; 

template<class T> bool ckmin(T& a, const T& b) { 
    return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
    return a < b ? a = b, 1 : 0; }
int pct(int x) { return __builtin_popcount(x); } 

namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);

    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class T, class... Ts> void re(T& t, Ts&... ts) { 
        re(t); re(ts...); 
    }

    template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = {a,b}; }
    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
}

using namespace input;

namespace output {
    void pr(int x) { cout << x; }
    void pr(long x) { cout << x; }
    void pr(ll x) { cout << x; }
    void pr(unsigned x) { cout << x; }
    void pr(unsigned long x) { cout << x; }
    void pr(unsigned long long x) { cout << x; }
    void pr(float x) { cout << x; }
    void pr(double x) { cout << x; }
    void pr(ld x) { cout << x; }
    void pr(char x) { cout << x; }
    void pr(const char* x) { cout << x; }
    void pr(const string& x) { cout << x; }
    void pr(bool x) { pr(x ? "true" : "false"); }
    template<class T> void pr(const complex<T>& x) { cout << x; }
    
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T> void pr(const T& x);
    
    template<class T, class... Ts> void pr(const T& t, const Ts&... ts) { 
        pr(t); pr(ts...); 
    }
    template<class T1, class T2> void pr(const pair<T1,T2>& x) { 
        pr("{",x.f,", ",x.s,"}"); 
    }
    template<class T> void pr(const T& x) { 
        pr("{"); // const iterator needed for vector<bool>
        bool fst = 1; for (const auto& a: x) pr(!fst?", ":"",a), fst = 0; 
        pr("}");
    }
    
    void ps() { pr("\n"); } // print w/ spaces
    template<class T, class... Ts> void ps(const T& t, const Ts&... ts) { 
        pr(t); if (sizeof...(ts)) pr(" "); ps(ts...); 
    }
    
    void pc() { pr("]\n"); } // debug w/ commas
    template<class T, class... Ts> void pc(const T& t, const Ts&... ts) { 
        pr(t); if (sizeof...(ts)) pr(", "); pc(ts...); 
    }
    #define dbg(x...) pr("[",#x,"] = ["), pc(x);
}

using namespace output;

namespace io {
    void setIn(string s) { freopen(s.c_str(),"r",stdin); }
    void setOut(string s) { freopen(s.c_str(),"w",stdout); }
    void setIO(string s = "") {
        ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
        // cin.exceptions(cin.failbit); 
        // throws exception when do smth illegal
        // ex. try to read letter into int
        if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
    }
}

using namespace io;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

/**
 * Description: Used only once. Finds all maximal cliques.
 * Time: O(3^{N/3})
 * Source: KACTL
 * Verification: BOSPRE 2016 gaudy
 */

namespace maximal {
    typedef bitset<128> B; B adj[128];
    int N, ans;
    // possibly in clique, not in clique, in clique
    void cliques(B P = ~B(), B X={}, B R={}) { 
        // ps("AA");
        if (!P.any()) { 
            if (!X.any()) ckmax(ans,(int)R.count()); // do smth with R
            return; 
        }
        int q = (P|X)._Find_first();
        // clique must contain q or non-neighbor of q
        B cands = P&~adj[q]; 
        F0R(i,N) if (cands[i]) {
            R[i] = 1; cliques(P&adj[i],X&adj[i],R);
            R[i] = P[i] = 0; X[i] = 1;
        }
    }
}

struct MaxClique {
    double limit=0.025, pk=0; // # of steps
    struct Vertex { int i, d=0; Vertex(int _i):i(_i){} };
    typedef vector<Vertex> vv; vv V;
    vector<bitset<200>> e; 
    vector<vi> C; // colors
    vi qmax, q, S, old; // max clique, current clique
    void init(vv& r) {
        each(v,r) v.d = 0; 
        each(v,r) each(j,r) v.d += e[v.i][j.i]; // degree
        sort(all(r), [](Vertex a,Vertex b) { return a.d > b.d; });
        int mxD = r[0].d; F0R(i,sz(r)) r[i].d = min(i,mxD)+1;
    }
    void expand(vv& R, int lev = 1) {
        S[lev] += S[lev-1]-old[lev]; old[lev] = S[lev-1]; // sum # steps up to lev
        while (sz(R)) {
            if (sz(q)+R.bk.d <= sz(qmax)) return; // can't make larger clique
            q.pb(R.bk.i); // insert node with max col into clique
            vv T; each(v,R) if (e[R.bk.i][v.i]) T.pb({v.i});
            if (sz(T)) {
                if (S[lev]++/++pk < limit) init(T); // recalc degs within set
                int j = 0, mxk = 1, mnk = max(sz(qmax)-sz(q)+1,1);
                C[1].clear(), C[2].clear();
                each(v,T) {
                    int k = 1; auto f = [&](int i) { return e[v.i][i]; };
                    while (any_of(all(C[k]),f)) k++; // inc color while common edge
                    if (k > mxk) mxk = k, C[mxk+1].clear(); // new set
                    if (k < mnk) T[j++].i = v.i;
                    C[k].pb(v.i);
                }
                if (j > 0) T[j-1].d = 0; // at least one vertex >= j is part of clique
                FOR(k,mnk,mxk+1) each(i,C[k]) T[j].i = i, T[j++].d = k;
                expand(T,lev+1);
            } else if (sz(q) > sz(qmax)) qmax = q;
            q.pop_back(), R.pop_back(); // R.bk not in set
        }
    }
    vi solve(vector<bitset<200>> conn) { 
        e = conn; C.rsz(sz(e)+1), S.rsz(sz(C)), old = S;
        F0R(i,sz(e)) V.pb({i}); 
        init(V), expand(V); return qmax; 
    }
};

int main() {
    F0R(it,100000) {
        int n =(rand()%32)+1;
        vector<bitset<200>> ed(n);
        F0R(i,n) maximal::adj[i].reset();
        int p =rand()%100;
        F0R(i,n) F0R(j,i) {
            ed[i][j] = (rand() % 100) < p;
            ed[j][i] = ed[i][j];
            maximal::adj[i][j] = ed[i][j];
            maximal::adj[j][i] = ed[j][i];
        }
        maximal::N = n, maximal::ans = 0; maximal::cliques();
        MaxClique clique2; 
        auto b = clique2.solve(ed);
        // ps("HUH",maximal::ans,sz(b));
        assert(maximal::ans == sz(b));
    }
    cout<<"Tests passed!"<<endl;
}
