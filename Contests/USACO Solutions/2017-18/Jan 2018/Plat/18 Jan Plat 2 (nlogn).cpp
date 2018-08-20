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
const int MX = 70001;

struct contain {
    vpi a;
    vi tmp;
    int mx = 0;
    bool done = 0;
    void upd(int d, int v) { 
        a.pb({d,v});
    }
    void init() {
        tmp.resize(mx+1);
        for (auto x: a) if (x.f <= mx) tmp[max(x.f,0)] += x.s;
        FOR(i,1,mx+1) tmp[i] += tmp[i-1];
        done = 1;
    }
    
    int query(int d) { // query d 
        if (!done) init();
        return tmp[d];
    }
};

int n, distLeaf[MX];
vi adj[MX];

void MXX(int& a, int b) { a = max(a,b); }

template<int SZ> struct centroidDecomp {
    int N;
    bool done[SZ];
    int sub[SZ], par[SZ];
    pi cen[SZ];
    contain A[SZ];
    vector<contain> B[SZ];
    vi dist[SZ];
    
    // INITIALIZE
    
    void dfs (int no) {
        sub[no] = 1;
        for (int i: adj[no]) if (!done[i] && i != par[no]) {
            par[i] = no;
            dfs(i);
            sub[no] += sub[i];
        }
    }
    
    void genDist(int par, int no, int dis) {
        dist[no].pb(dis);
        MXX(A[cen[no].f].mx,dis);
        MXX(B[cen[no].f][cen[no].s].mx,dis);
        for (int i: adj[no]) if (!done[i] && i != par) {
            cen[i] = cen[no];
            genDist(no,i,dis+1);
        }
    }
    
    int getCentroid(int x) {
        par[x] = 0; dfs(x);
        int sz = sub[x];
        while (1) {
            pi mx = {0,0};
            for (int i: adj[x]) if (!done[i] && i != par[x]) mx = max(mx,{sub[i],i});
            if (mx.f*2 > sz) x = mx.s;
            else return x;
        }
    }
    
    void solve (int x) {
        x = getCentroid(x); done[x] = 1;
        int co = 0;
        for (int i: adj[x]) if (!done[i]) {
            cen[i] = {x,co++};
            B[x].pb(contain());
            genDist(x,i,1);
        }
        for (int i: adj[x]) if (!done[i]) solve(i);
    }
    
    // QUERY 
    
    void upd(int x, int d, int v) {
        pi X = {x,-1};
        int ind = sz(dist[x]);
        for (; X.f; X = cen[X.f], ind --) {
            int D = d; if (ind < sz(dist[x])) D -= dist[x][ind];
            A[X.f].upd(D,v);
            if (X.s != -1) B[X.f][X.s].upd(D,v);
        }
    }
    
    int query(int x) {
        int ans = 0;
        pi X = {x,-1};
        int ind = sz(dist[x]);
        for (; X.f; X = cen[X.f], ind --) {
            int D = 0; if (ind < sz(dist[x])) D = dist[x][ind];
            ans += A[X.f].query(D);
            if (X.s != -1) ans -= B[X.f][X.s].query(D);
        }
        return ans;
    }
};

centroidDecomp<MX> c;

int dfs(int cur, int pre) {
    distLeaf[cur] = MOD;
    for (int i: adj[cur]) if (i != pre) {
        dfs(i,cur);
        distLeaf[cur] = min(distLeaf[cur],distLeaf[i]+1);
    }
    if (sz(adj[cur]) == 1) distLeaf[cur] = 0;
    return distLeaf[cur];
}

void dfs2(int cur, int pre) {
    if (cur != 1) distLeaf[cur] = min(distLeaf[cur],distLeaf[pre]+1);
    for (int i: adj[cur]) if (i != pre) dfs2(i,cur);
}

void input() {
    freopen("atlarge.in","r",stdin);
    freopen("atlarge.out","w",stdout);
    cin >> n;
    F0R(i,n-1) {
        // int a = i+1,b = i+2; 
        int a,b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    dfs(1,0);
    dfs2(1,0);
}

int main() {
    input();
    c.solve(1);
    FOR(i,1,n+1) c.upd(i,distLeaf[i],2-sz(adj[i]));
    // add 2-deg(x) to ans[y] if dist(y,closest leaf) <= dist(x,y)
    FOR(i,1,n+1) {
        if (sz(adj[i]) == 1) cout << 1;
        else cout << c.query(i);
        cout << "\n";
    }
}

/* Look for:
* the exact constraints (multiple sets are too slow for n=10^6 :( ) 
* special cases (n=1?)
* overflow (ll vs int?)
* array bounds
* if you have no idea just guess the appropriate well-known algo instead of doing nothing :/
*/