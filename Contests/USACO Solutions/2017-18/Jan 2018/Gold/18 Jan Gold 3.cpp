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
 
int N,M,K;
ll ans[1000001];
 
int main() {
    freopen("spainting.in","r",stdin);
    freopen("spainting.out","w",stdout);
     
    cin >> N >> M >> K;
    ans[0] = 1;
    FOR(i,1,N+1) {
        ans[i] = M*ans[i-1];
        if (i == K) ans[i] -= M;
        else if (i > K) ans[i] -= (M-1)*ans[i-K];
        ans[i] = (ans[i]%MOD+MOD)%MOD;
    }
    ll ret = 1;
    F0R(i,N) ret = ret*M % MOD;
    ret -= ans[N];
    ret = (ret%MOD+MOD)%MOD;
    cout << ret;
}
 
// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
