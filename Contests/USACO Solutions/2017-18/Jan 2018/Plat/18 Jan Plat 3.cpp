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
const int MX = 100000;

ll N, hei[MX], lo[MX], hi[MX];
ll cumlo[MX][2], cumhi[MX][2];
ll ans = 0;

ll getlo (int ind, int L, int R) {
    return ((cumlo[R+1][ind]-cumlo[L][ind])%MOD+MOD)%MOD;
}

ll gethi (int ind, int L, int R) {
    return ((cumhi[R+1][ind]-cumhi[L][ind])%MOD+MOD)%MOD;
}

void query(int ind) {
	// (hi[i]-lo[i]+2)*(hi[i]-lo[i]+1)
	
	int L = ind-1, R = N-2;
	while (L < R) {
	    int M = (L+R+1)/2;
	    if (hi[M] >= lo[ind]) L = M;
	    else R = M-1;
	}
	ans += gethi(1,ind,L);
	ans -= 2*gethi(0,ind,L)*lo[ind];
	ans += (L+1-ind)*lo[ind]*lo[ind];
	ans += 3*(gethi(0,ind,L)-(L+1-ind)*lo[ind]);
	ans += 2*(L+1-ind);
	ans %= MOD;
}

int main() {
	freopen("sprinklers.in","r",stdin);
	freopen("sprinklers.out","w",stdout);
	cin >> N;
	F0R(i,N) {
	    int a,b; cin >> a >> b;
	    hei[a] = b;
	}
	F0R(i,N-1) {
	    lo[i] = hei[i];
	    if (i > 0) lo[i] = min(lo[i],lo[i-1]);
	}
	F0Rd(i,N-1) {
	    hi[i] = hei[i+1]-1;
	    if (i < N-2) hi[i] = max(hi[i],hi[i+1]);
	}
	
	F0R(i,N-1) {
	    cumlo[i+1][0] = lo[i], cumlo[i+1][1] = lo[i]*lo[i];
	    cumhi[i+1][0] = hi[i], cumhi[i+1][1] = hi[i]*hi[i];
	    F0R(j,2) {
	        cumlo[i+1][j] += cumlo[i][j];
	        cumlo[i+1][j] %= MOD;
	        cumhi[i+1][j] += cumhi[i][j];
	        cumhi[i+1][j] %= MOD;
	    }
	}
	F0R(i,N-1) query(i);
	ans *= (MOD+1)/2;
	ans = (ans%MOD+MOD)%MOD;
	cout << ans;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
