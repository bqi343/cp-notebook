/*
ID: bqi3431
PROG: bigbrn
LANG: C++11
*/

//#include <iostream>
#include <fstream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
const int MOD = 1000000007;
double PI = 4*atan(1);

bool x[1001][1001];
int sq[1001][1001];

int main() {
	ifstream cin ("bigbrn.in");
	ofstream cout ("bigbrn.out");
	ios_base::sync_with_stdio(0);cin.tie(0);
	int N,T; cin >> N >> T;
	F0R(i,T) {
		int a1, a2; cin >> a1 >> a2;
		x[a1-1][a2-1] = 1;
	}
	int ans = 0;
	F0Rd(i,N) F0Rd(j,N) if (x[i][j] == 0) {
		sq[i][j] = 1+min(min(sq[i][j+1],sq[i+1][j]),sq[i+1][j+1]);
		ans = max(ans,sq[i][j]);
	}
	cout << ans << "\n";
}
