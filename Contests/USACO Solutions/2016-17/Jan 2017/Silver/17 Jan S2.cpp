// #include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<unordered_map>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

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

int b1[3][100000], n, ans=0;

int main() {
	ifstream cin ("hps.in");
	ofstream cout ("hps.out");
	cin >> n;
	F0R(i,n) {
		char c; cin >> c;
		if (i) {
			b1[0][i] = b1[0][i-1];
			b1[1][i] = b1[1][i-1];
			b1[2][i] = b1[2][i-1];
		}
		// H=0,P=1,S=2
		if (c == 'H') b1[1][i] ++;
		else if (c == 'P') b1[2][i] ++;
		else b1[0][i] ++;
	}
	F0R(i,n) {
		int z = max(max(b1[0][i],b1[1][i]),b1[2][i]);
		z += max(max(b1[0][n-1]-b1[0][i],b1[1][n-1]-b1[1][i]),b1[2][n-1]-b1[2][i]);
		ans = max(ans,z);
	}
	cout << ans;
}
