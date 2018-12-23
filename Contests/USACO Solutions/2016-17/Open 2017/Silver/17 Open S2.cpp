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

int N,M, ans;
string A[500], B[500];

int hsh(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'T') return 2;
    if (c == 'G') return 3;
}

int main() {
    freopen("cownomics.in","r",stdin);
    freopen("cownomics.out","w",stdout);
	cin >> N >> M;
	F0R(i,N) cin >> A[i];
	F0R(i,N) cin >> B[i];
	F0R(i,M) FOR(j,i+1,M) FOR(k,j+1,M) {
        bitset<64> b; 
	    F0R(t,N) {
	        int o = hsh(A[t][i])+4*hsh(A[t][j])+16*hsh(A[t][k]);
	        b[o] = 1;
	    }
	    bool f = 0;
	    F0R(t,N) {
	        int o = hsh(B[t][i])+4*hsh(B[t][j])+16*hsh(B[t][k]);
	        if (b[o]) {
	            f = 1;
	            break;
	        }
	    }
	    ans += (f^1);
	}
	cout << ans;
}

// read!
// ll vs. int!
