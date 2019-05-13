// see http://codeforces.com/problemset/problem/690/C3

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pi;
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

int Q, anc[MX][17], comp[MX], depth[MX], cur = 0;
pi dia[MX];

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a,b);
    F0Rd(i,17) if ((depth[a]-depth[b])&(1<<i)) a = anc[a][i];
    if (a == b) return a;
    F0Rd(i,17) if (anc[a][i] != anc[b][i]) {
        a = anc[a][i];
        b = anc[b][i];
    }
    return anc[a][0];
}

int dist(int a, int b) {
    return depth[a]+depth[b]-2*depth[lca(a,b)];
}

int main() {
    freopen("newbarn.in","r",stdin);
    freopen("newbarn.out","w",stdout);
    cin >> Q;
    F0R(i,Q) {
        char c; int x; cin >> c >> x;
        if (c == 'B') {
            cur ++;
            if (x == -1) {
                dia[comp[cur] = cur] = {cur,cur};
            } else {
                comp[cur] = comp[x];
                depth[cur] = depth[x]+1;
                
                anc[cur][0] = x;
                FOR(i,1,17) anc[cur][i] = anc[anc[cur][i-1]][i-1];
                
                int d = dist(dia[comp[cur]].f,dia[comp[cur]].s);
                if (dist(cur,dia[comp[cur]].f) > d) dia[comp[cur]].s = cur;
                else if (dist(cur,dia[comp[cur]].s) > d) dia[comp[cur]].f = cur;
            }
        } else {
            cout << max(dist(dia[comp[x]].f,x),dist(dia[comp[x]].s,x)) << "\n";
        }
    }
}

// read the question correctly (is y a vowel?)
// look out for special cases (n=1?) and overflow (ll vs int?)
