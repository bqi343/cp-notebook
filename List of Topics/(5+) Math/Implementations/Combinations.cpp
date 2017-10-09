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

ll fac[5001], ifac[5001];

ll po (ll b, ll p) {
    return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD;
}

ll inv (ll b) { return po(b,MOD-2); }

ll comb(ll a, ll b) {
    if (a < b) return 0;
    ll tmp = fac[a]*ifac[b] % MOD;
    tmp = tmp*ifac[a-b] % MOD;
    return tmp;
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	fac[0] = ifac[0] = 1;
	FOR(i,1,5001) {
	    fac[i] = i*fac[i-1] % MOD;
	    ifac[i] = inv(fac[i]);
	}
	cout << comb(5,3);
}

// read!
// ll vs. int!
