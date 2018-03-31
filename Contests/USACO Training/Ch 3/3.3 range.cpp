/*
ID: bqi3431
PROG: range
LANG: C++11
*/

//#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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

ifstream cin ("range.in");
ofstream cout ("range.out");

int main() {
	int N; cin >> N;
	bool ar[250][250];
	F0R(i,N)F0R(j,N) {
		char x; cin >> x;
		ar[i][j] = (x-'0');
	}
	FOR(i,2,N+1) {
		int ans = 0;
		F0R(j,N-i+1) F0R(k,N-i+1) {
			ar[j][k] = (ar[j][k]&ar[j][k+1]&ar[j+1][k]&ar[j+1][k+1]);
			ans += ar[j][k];
		}
		if (ans == 0) break;
		cout << i << " " << ans << "\n";
	}
}
