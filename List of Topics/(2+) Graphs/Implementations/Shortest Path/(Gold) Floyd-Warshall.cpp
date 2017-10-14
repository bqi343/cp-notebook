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
const ll INF = 1e18;

int n,m,q;
ll dist[150][150], bad[150][150];

void solve() {
    F0R(i,n) F0R(j,n) dist[i][j] = INF, bad[i][j] = 0;
    F0R(i,n) dist[i][i] = 0;
    F0R(i,m) {
        int u,v,w; cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v],(ll)w);
    }
    F0R(k,n) F0R(i,n) F0R(j,n) if (dist[i][k] != INF && dist[k][j] != INF) 
        dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
    
    F0R(k,n) F0R(i,n) F0R(j,n) if (dist[i][k] != INF && dist[k][j] != INF)  
        if (dist[i][j] > dist[i][k]+dist[k][j])
            bad[i][j] = 1;
            
    F0R(k,n) F0R(i,n) F0R(j,n) {
        if (dist[i][k] < INF && bad[k][j]) bad[i][j] = 1;
        if (bad[i][k] && dist[k][j] < INF) bad[i][j] = 1;
    }
    
    F0R(i,q) {
        int u,v; cin >> u >> v;
        if (bad[u][v]) cout << "-Infinity\n";
        else if (dist[u][v] == INF) cout << "Impossible\n";
        else cout << dist[u][v] << "\n";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    while (cin >> n >> m >> q) solve();
}

// read!
// ll vs. int!