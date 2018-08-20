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

int N;
ll M, F[MX], S[MX];
int ans = MOD;
deque<pi> d;

int main() {
    freopen("haybalefeast.in","r",stdin);
    freopen("haybalefeast.out","w",stdout);
	cin >> N >> M;
	F0R(i,N) cin >> F[i] >> S[i];
	int r = -1;
	ll sum = 0;
	F0R(i,N) {
	    if (sz(d) && d.front().s == i-1) d.pop_front();
	    if (i) sum -= F[i-1];
	    while (r < N-1 && sum < M) {
	        sum += F[++r];
	        while (sz(d) && d.back().f <= S[r]) d.pop_back();
	        d.pb({S[r],r});
	    }
	    if (sum >= M) ans = min(ans,d.front().f);
	}
	cout << ans;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
