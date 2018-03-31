#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

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

vi pairs[26];

int main() {
	string x; cin >> x;
	F0R(i,x.length()) pairs[x[i]-'A'].pb(i);
	int ans = 0;
	F0R(i,26) F0R(j,26) 
		if (i != j) 
			if (pairs[i][0]<pairs[j][0] && pairs[i][1] > pairs[j][0] && pairs[j][1] > pairs[i][1]) 
				ans++;
	
	cout << ans;
}
