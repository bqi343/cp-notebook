// Euler Tour LCA w/ O(1) query

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
pii rmq[MAXK][2*MAXN];
int depth[MAXN], pos[MAXN];

int N,Q,nex=0;

void dfs(int u, int prev){
    pos[u] = nex; depth[u] = depth[prev]+1;
    rmq[0][nex++] = {depth[u],u};
    for (int v: edges[u]) if (v != prev) {
        dfs(v, u);
        rmq[0][nex++] = {depth[u],u};
    }
}

int query(int u, int v){
    int x = 31-__builtin_clz(v-u+1);
    return min(rmq[x][u],rmq[x][v-(1<<x)+1]).s;
}

int main(){
    int u, v, root;
    cin >> N >> Q >> root;
    F0R(i,N-1) {
        cin >> u >> v;
        edges[u].pb(v), edges[v].pb(u);
    }
    dfs(root, 0);
    FOR(k,1,MAXK) F0R(i,nex) if (i+(1<<(k-1)) < nex) rmq[k][i] = min(rmq[k-1][i],rmq[k-1][i+(1<<(k-1))]);
    
    F0R(i,Q) {
        cin >> u >> v;
        u = pos[u], v = pos[v];
        if (u > v) swap(u,v);
        cout << query(u,v) << "\n";
    }
}
