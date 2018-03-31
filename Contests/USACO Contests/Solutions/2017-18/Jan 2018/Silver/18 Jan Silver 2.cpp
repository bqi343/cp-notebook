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
 
int N,M,R;
vi c, r;
ll cum[100001], ans, t;
vector<pi> tmp;
 
int main() {
    freopen("rental.in","r",stdin);
    freopen("rental.out","w",stdout);
    cin >> N >> M >> R;
     
    c.resize(N);
    F0R(i,N) cin >> c[i];
    sort(c.rbegin(),c.rend());
    F0R(i,M) {
        int Q,P; cin >> Q >> P;
        tmp.pb({P,Q});
    }
    sort(all(tmp));
     
    r.resize(R);
    F0R(i,R) cin >> r[i];
    sort(r.rbegin(),r.rend());
     
    F0R(i,sz(r)) cum[i+1] = cum[i]+r[i];
    F0R(i,N+1) {
        ans = max(ans,t+cum[min(R,N-i)]);
        if (i == N) break;
        int cur = c[i];
        while (sz(tmp) && cur > 0) {
            ll z = min(tmp.back().s,cur);
            tmp.back().s -= z, cur -= z;
            t += z*tmp.back().f;
            if (tmp.back().s == 0) tmp.pop_back();
        }
    }
    cout << ans;
}
 
// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
