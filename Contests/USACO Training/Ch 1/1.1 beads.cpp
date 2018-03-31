/*
ID: bqi3431
PROG: beads
LANG: C++11
*/

// #include <iostream>
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

int main() {
	ifstream cin ("beads.in");
	ofstream cout ("beads.out");
	int N, ans = 0; cin >> N;
	string s; cin >> s;
	s += s;
	F0R(i,s.length()-1) {
		int l = i, r = i+1;
		char l1 = s[i], r1 = s[i+1];
		while (l>0) {
			if (l1 == 'w' || s[l-1] == 'w' || s[l-1] == l1) {
				l--;
				if (s[l] != 'w') l1 = s[l];
			}
			else break;
		}
		
		while (r<s.length()-1) {
			if (r1 == 'w' || s[r+1] == 'w' || s[r+1] == r1) {
				r++;
				if (s[r] != 'w') r1 = s[r];
			}
			else break;
		}
		ans = max(ans,r-l+1);
	}
	ans = min(ans,N);
	cout << ans << "\n";
}
