#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;

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
const double PI = 4*atan(1);
const ll INF = 1e18;
const int MX = 50001;

vpi adj[MX];
int N,M,ans[MX]; 

struct {
    int par[16][MX], mn[16][MX];
    int key[MX], depth[MX];
    
    void dfs(int cur) {
        for (auto a: adj[cur]) if (a.f != par[0][cur]) {
            par[0][a.f] = cur;
            key[a.f] = a.s;
            depth[a.f] = depth[cur]+1;
            dfs(a.f);
        }
    }
    
    void gen() {
        FOR(i,1,N+1) key[i] = -1;
        F0R(j,16) FOR(i,1,N+1) mn[j][i] = MOD;
        dfs(1);
        FOR(j,1,16) FOR(i,1,N+1) par[j][i] = par[j-1][par[j-1][i]];
    }
    
    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a,b);
        F0Rd(i,16) if ((depth[a]-depth[b])&(1<<i)) a = par[i][a];
        F0Rd(i,16) if (par[i][a] != par[i][b]) a = par[i][a], b = par[i][b];
        if (a == b) return a;
        return par[0][a];
    }
    
    void AD(int a, int x, int c) {
        F0Rd(i,16) if (x&(1<<i)) {
            mn[i][a] = min(mn[i][a],c);
            a = par[i][a];
        }
    }
    
    void ad(int a, int b, int c) {
        int x = lca(a,b);
        // cout << a << " " << b << " " << x << "\n";
        AD(a,depth[a]-depth[x],c);
        AD(b,depth[b]-depth[x],c);
    }
    
    void push() {
        FORd(j,1,16) FOR(i,1,N+1) {
            mn[j-1][i] = min(mn[j-1][i],mn[j][i]);
            mn[j-1][par[j-1][i]] = min(mn[j-1][par[j-1][i]],mn[j][i]);
        }
    }
} L;

int main() {
    freopen("disrupt.in","r",stdin);
    freopen("disrupt.out","w",stdout);
    cin >> N >> M;
    F0R(i,N-1) {
        int p,q; cin >> p >> q;
        adj[p].pb({q,i}), adj[q].pb({p,i});
    }
    L.gen();
    F0R(i,M) {
        int p,q,r; cin >> p >> q >> r;
        // cout << p << " " << q << " " << r << "\n";
        L.ad(p,q,r);
    }
    L.push();
    FOR(i,1,N+1) if (L.key[i] != -1) {
        if (L.mn[0][i] == MOD) ans[L.key[i]] = -1;
        else ans[L.key[i]] = L.mn[0][i];
    }
    F0R(i,N-1) cout << ans[i] << "\n";
}

// read the question correctly (is y a vowel?)
// look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)