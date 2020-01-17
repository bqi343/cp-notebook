// help idk what this is even doing anymore

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
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const int MX = 70001;

int N;
set<pi> testChange[MX];
vi adj[MX];
map<pi,int> closeLeaf, dp;

int recalc(pi node, int num) {
    if (num >= closeLeaf[node]) return 1;
    int x = 0;
    for (int i: adj[node.s]) if (i != node.f) x += dp[{node.s,i}];
    return x;
}

void input() {
    freopen("atlarge.in","r",stdin);
    freopen("atlarge.out","w",stdout);
    cin >> N;
    F0R(i,N-1) {
        int a,b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    FOR(i,1,N+1) for (int j: adj[i]) dp[{i,j}] = 1;
}

set<int> lef[MX];
queue<pi> todo;

void genCloseLeaf() {
    FOR(i,1,N+1) for (int j: adj[i]) lef[i].insert(j);
    FOR(i,1,N+1) if (sz(adj[i]) == 1) {
        for (int j: adj[i]) {
            closeLeaf[{j,i}] = 0;
            todo.push({j,i});
            lef[i].erase(j);
        }
    }
    while (sz(todo) > 0) {
        auto a = todo.front(); todo.pop();
        for (int i: lef[a.f]) if (i != a.s) {
            closeLeaf[{i,a.f}] = closeLeaf[a]+1;
            todo.push({i,a.f});
            lef[a.f].erase(i);
        }
    }
    for (auto a: closeLeaf) if (a.s > 0) testChange[a.s-1].insert(a.f);
}

set<pi> done;

void calcVals() { // help I have no idea what this is doing lol
    FORd(i,1,N) {
        vector<pair<pi,int>> change;
        for (pi j: testChange[i]) {
            int DPJ = recalc(j,i);
            if (DPJ != dp[j]) change.pb({j,DPJ});
        }
        for (auto a: change) {
            dp[a.f] = a.s;
            if (i > 0) for (int j: adj[a.f.f]) if (j != a.f.s) 
                testChange[i-1].insert({j,a.f.f});
        }
    }
}

int ans[MX];

void finish() {
    for (auto a: dp) ans[a.f.f] += a.s;
    FOR(i,1,N+1) {
        if (sz(adj[i]) == 1) cout << "1\n";
        else cout << ans[i] << "\n";
    }
}

int main() {
    input();
    genCloseLeaf();
    calcVals();
    finish();
}
