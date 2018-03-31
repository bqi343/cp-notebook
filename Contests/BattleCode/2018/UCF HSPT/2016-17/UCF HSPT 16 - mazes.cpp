#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
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

int xdir[4] = {1,0,-1,0}, ydir[4] = {0,1,0,-1};
int dist[300][300];
char g[300][300];
int r,c, ans; 

void solve() {
    ans = 0;
    F0R(i,r) F0R(j,c) dist[i][j] = MOD;
    deque<pi> todo;
    F0R(i,r) F0R(j,c) if (g[i][j] == 'S') {
        dist[i][j] = 0;
        todo.push_front({i,j});
    }
    while (todo.size()) {
        pi x = todo.front(); todo.pop_front();
        F0R(i,4) {
            pi nx = {x.f+xdir[i], x.s+ydir[i]};
            if (nx.f < 0 || nx.f >= r || nx.s < 0 || nx.s >= c) continue;
            
            if (g[nx.f][nx.s] != '#') {
                if (dist[x.f][x.s] < dist[nx.f][nx.s]) {
                    dist[nx.f][nx.s] = dist[x.f][x.s];
                    todo.push_front(nx);
                }
            } else  {
                if (dist[x.f][x.s]+1 < dist[nx.f][nx.s]) {
                    dist[nx.f][nx.s] = dist[x.f][x.s]+1;
                    todo.push_back(nx);
                }
            }
        }
    }
    F0R(i,r) F0R(j,c) if (g[i][j] == 'E') ans = dist[i][j];
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n; cin >> n;
    F0R(i,n) {
        cin >> r >> c;
        F0R(j,r) F0R(k,c) cin >> g[j][k];
        solve();
        cout << "Maze #" << (i+1) << ": " << ans << "\n";
    }
}

// read!
// ll vs. int!
