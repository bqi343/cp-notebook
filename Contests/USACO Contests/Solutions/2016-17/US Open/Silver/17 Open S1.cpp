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

int N, ans;
vector<pi> v;

int main() {
    freopen("pairup.in","r",stdin);
    freopen("pairup.out","w",stdout);
    cin >> N; v.resize(N);
    F0R(i,N) cin >> v[i].s >> v[i].f;
    sort(v.begin(),v.end());
    int i1 = 0, i2 = v.size()-1;
    while (i1 < i2) {
        ans = max(ans,v[i1].f+v[i2].f);
        int t = min(v[i1].s,v[i2].s);
        v[i1].s -= t, v[i2].s -= t;
        if (v[i1].s == 0) i1++;
        if (v[i2].s == 0) i2--;
    }
    if (i1 == i2 && v[i1].s > 0) ans = max(ans,2*v[i1].f);
    cout << ans;
}

// read!
// ll vs. int!
