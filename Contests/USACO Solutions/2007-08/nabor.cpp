/*
 ID: bqi3431
 PROG: nabor
 LANG: C++11
 */
 
 // copied from https://csacademy.com/contest/round-84/task/the-sprawl/

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

const int maxn = 100010; 

int n;
vector<int> adj[maxn], cost[maxn]; 

struct UnionFind {
    int p[maxn];
    void init(int n) { for(int i = 1; i <= n; i++)  p[i] = i; }
    int find(int u) { return p[u] == u ? u : p[u] = find(p[u]); }
    void Union(int u, int v) { p[find(u)] = find(v); }
} dsu;

struct point {
    int x, y, index;
    bool operator < (const point &p) const { 
        return x == p.x ? y < p.y : x < p.x; 
    }
} p[maxn];

int dist(point &a, point &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
struct edge { 
    int u, v, c; 
    bool operator < (const edge &p) const {
        return c < p.c;
    }
}; 
struct node { int value, p; } T[maxn];
 
int query(int x) {
    int r = INT_MAX, p = -1;
    for(; x <= n; x += (x & -x)) 
        if(T[x].value < r) r = T[x].value, p = T[x].p;
    return p;
}
void update(int x, int w, int p) {
    for(; x > 0; x -= (x & -x)) if(T[x].value > w) T[x].value = w, T[x].p = p;
} 
 
vector<edge> edgelist; 
 
void addEdge(int u, int v, int c) { 
    edgelist.push_back({u, v, c});
} 

void kruskal() { 
    dsu.init(n); 
    sort(edgelist.begin(), edgelist.end());
    for(edge e : edgelist) {
        int u = e.u, v = e.v, c = e.c;
        if(dsu.find(u) != dsu.find(v)) {
            adj[u].push_back(v);
            adj[v].push_back(u);
            cost[u].push_back(c);
            cost[v].push_back(c); 
            dsu.Union(u, v);
        }
    }
}

void manhattan() {
    for(int i = 1; i <= n; ++i) p[i].index = i;
    for(int dir = 1; dir <= 4; ++dir) {
        if(dir == 2 || dir == 4) {
            for(int i = 1; i <= n; ++i) swap(p[i].x, p[i].y);
        } else if(dir == 3) {
            for(int i = 1; i <= n; ++i) p[i].x = -p[i].x;
        } sort(p + 1, p + 1 + n);
        vector<int> v; static int a[maxn];
        for(int i = 1; i <= n; ++i) a[i] = p[i].y - p[i].x, v.push_back(a[i]);
        sort(v.begin(), v.end()); 
        v.erase(unique(v.begin(), v.end()), v.end());
        for(int i = 1; i <= n; ++i) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        for(int i = 1; i <= n; ++i) T[i].value = INT_MAX, T[i].p = -1;
        for(int i = n; i >= 1; --i) {
            int pos = query(a[i]);
            if(pos != -1) addEdge(p[i].index, p[pos].index, dist(p[i], p[pos]));
            update(a[i], p[i].x + p[i].y, i);
        }
    } 
}

// https://www.codechef.com/viewsolution/16162344

ll ans = 0;
template<int SZ> struct DSU {
    int par[SZ], sz[SZ];
    DSU() {
        F0R(i,SZ) par[i] = i, sz[i] = 1;
    }
    
    int get(int x) { // path compression
    	if (par[x] != x) par[x] = get(par[x]);
    	return par[x];
    }
    
    bool unite(ll t, int x, int y) { // union-by-rank
    	x = get(x), y = get(y);
    	ans += t*sz[x]*sz[y];
    	// cout << "OH " << t << " " << sz[x] << " " << sz[y] << "\n";
    	if (x == y) return 0;
    	if (sz[x] < sz[y]) swap(x,y);
    	sz[x] += sz[y], par[y] = x;
    	return 1;
    }
};

DSU<MX> D; 
int c;
vector<array<int,3>> ed;

int main() {
    // you should actually read the stuff at the bottom
    setIO("nabor"); 
    
    cin >> n >> c;
    FOR(i,1,n+1) cin >> p[i].x >> p[i].y;
    manhattan();
    kruskal();
    FOR(i,1,n+1) {
        F0R(j,sz(cost[i])) if (adj[i][j] > i) {
            ed.pb({cost[i][j],i,adj[i][j]});
            //cout << i << " " << adj[i][j] << " " << cost[i][j]/2 << "\n";
        }
    }
    sort(all(ed));
    for (auto a: ed) if (a[0] <= c) D.unite(a[0],a[1],a[2]);
    int a = 0, b = 0;
    FOR(i,1,n+1) if (D.get(i) == i) {
        a ++;
        ckmax(b,D.sz[i]);
    }
    pr(a,b);
    
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/
