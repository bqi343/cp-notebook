// http://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/

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

vi adj[100001];
vector<pii> bridge;
int n,m, disc[100001], low[100001], art[100001], nex = 1;

void dfs(int pre, int node) {
    low[node] = disc[node] = nex++;
    
    int child = 0;
    for (int i: adj[node]) if (i != pre) {
        if (!disc[i]) {
            child++; dfs(node,i);
            if (disc[node] < low[i]) bridge.pb({node,i}); // check for bridge
            
            if (pre == 0) { // check for articulation point
                if (child > 1) art[node] = 1;
            } else if (disc[node] <= low[i]) art[node] = 1;
            
            low[node] = min(low[node],low[i]);
        } else low[node] = min(low[node],disc[i]);
    }
}

int main() {
    cin >> n >> m;
    F0R(i,m) {
        int x,y; cin >> x >> y;
        adj[x].pb(y), adj[y].pb(x);
    }
    dfs(0,1);
    cout << "Bridges\n";
    for (pii x: bridge) cout << x.f << " " << x.s << "\n";
    cout << "\n";
    
    cout << "Articulation Points\n";
    FOR(i,1,n+1) if (art[i]) cout << i << "\n";
}