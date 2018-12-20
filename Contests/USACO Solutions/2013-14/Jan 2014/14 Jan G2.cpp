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

int M,N, a[100][100], A[100][100], done[100][100];

bool test(int mid) {
    F0R(i,M) F0R(j,N) {
        A[i][j] = a[i][j];
        assert(A[i][j] != 0);
        done[i][j] = 0;
    }
    bool f = 1;
    while (f) {
        f = 0;
        F0R(i,M-mid+1) F0R(j,N-mid+1) if (!done[i][j]) {
            int x = 0;
            FOR(i1,i,i+mid) {
                FOR(j1,j,j+mid) if (A[i1][j1] != 0) {
                    x |= (1<<A[i1][j1]);
                    if (x == 6) break;
                }
                if (x == 6) break;
            }
            if (x != 6) {
                FOR(i1,i,i+mid) FOR(j1,j,j+mid) A[i1][j1] = 0;
                done[i][j] = 1;
                f = 1;
            }
        }
        bool done = 1;
        F0R(i,M) F0R(j,N) if (A[i][j] != 0) done = 0;
        if (done) return 1;
    }
    return 0;
}

int main() {
    freopen("skicourse.in","r",stdin);
    freopen("skicourse.out","w",stdout);
	cin >> M >> N;
	F0R(i,M) F0R(j,N) {
	    char c; cin >> c;
	    if (c == 'R') a[i][j] = 1;
	    else a[i][j] = 2;
	}
	test(11);
	int lo = 1, hi = min(M,N);
	while (lo < hi) {
	    int mid = (lo+hi+1)/2;
	    if (test(mid)) lo = mid;
	    else hi = mid-1;
	}
	cout << lo;
}

// read!
// ll vs. int!
