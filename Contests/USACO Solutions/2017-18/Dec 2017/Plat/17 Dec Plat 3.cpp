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

int N;
int co[100000], c[100000];

bool ok(int mid) {
    memset(co,0,sizeof co);
    F0R(i,mid) co[c[i]] ++;
    F0Rd(i,N) {
        if (i+co[i] >= N) return 0;
        if (i) co[i-1] += co[i];
    }
    return 1;
}

int main() {
	freopen("greedy.in","r",stdin);
	freopen("greedy.out","w",stdout);
	cin >> N;
	F0R(i,N) cin >> c[i];
	
	int lo = 0, hi = N;
	while (lo < hi) {
	    int mid = (lo+hi)/2;
	    if (ok(mid)) lo = mid+1;
	    else hi = mid;
	}
	cout << N-lo;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
