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

int n, a[100001], vis[100001], ans;

void dfs(int x) {
    int X = x;
    while (vis[x] == 0) {
        vis[x] = X;
        x = a[x];
    }
    if (vis[x] != X) return;
    while (vis[x] != -1) {
        vis[x] = -1;
        x = a[x];
    }
}

int main() {
    freopen("shuffle.in","r",stdin);
    freopen("shuffle.out","w",stdout);
    cin >> n;
    FOR(i,1,n+1) cin >> a[i];
    FOR(i,1,n+1) {
        if (vis[i] == 0) dfs(i);
        if (vis[i] == -1) {
            ans++;
        }
    }
    cout << ans;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
