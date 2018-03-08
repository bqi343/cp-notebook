#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

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
const int MX = 100001;

int n;
ll ans = INF, sz[MX];
string name[MX];
vi adj[MX];

ll dfs(int no, int cur) {
    if (sz(adj[no]) == 0) {
        sz[no] = 1;
        return cur+sz(name[no]);
    }
    if (no != 1) cur += sz(name[no])+1;
    ll z = 0;
    for (int a: adj[no]) {
        z += dfs(a,cur);
        sz[no] += sz[a];
    }
    return z;
}

void dfs2(int no, ll cur) {
    if (sz(adj[no]) == 0) return;
    ans = min(ans,cur);
    for (int a: adj[no]) 
        dfs2(a,cur-sz[a]*(sz(name[a])+1)+(sz[1]-sz[a])*3);
}

int main() {
    // freopen("dirtraverse.in","r",stdin);
    // freopen("dirtraverse.out","w",stdout);
    
    cin >> n;
    FOR(i,1,n+1) {
        cin >> name[i];
        int m; cin >> m;
        F0R(j,m) {
            int x; cin >> x;
            adj[i].pb(x);
        }
    }
    dfs2(1,dfs(1,0));
    cout << ans;
}

// read the question correctly (is y a vowel?)
// look out for special cases (n=1?) and overflow (ll vs int?)
