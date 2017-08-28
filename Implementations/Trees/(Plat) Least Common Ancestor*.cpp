// Debug the Bugs

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
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

const int MOD = 1000000007;
const int MAXN = 100001, MAXK = 20;

vi edges[MAXN];
int parK[MAXK][MAXN];
int depth[MAXN],wei[MAXN];

int V,Q;

void dfs(int u, int prev){
    parK[0][u] = prev;
    depth[u] = depth[prev]+1;
    for (int v: edges[u]) if (v != prev) dfs(v, u);
}

int lca(int u, int v){
    if (depth[u] < depth[v]) swap(u,v);
    
    F0Rd(k,MAXK)  if (depth[u]>=depth[v]+(1<<k))  u = parK[k][u];
    F0Rd(k,MAXK) if(parK[k][u] != parK[k][v]) u = parK[k][u], v = parK[k][v];
    
    if(u != v) u = parK[0][u], v = parK[0][v];
    return u;
}

int main(){
    int u, v, root;
    cin >> V >> Q >> root;
    F0R(i,V-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    dfs(root, -1);
    
    FOR(k,1,MAXK) FOR(i,1,V+1)
    parK[k][i] = parK[k-1][parK[k-1][i]];
    
    F0R(i,Q) {
        cin >> u >> v;
        cout << lca(u,v) << "\n";
    }
}
