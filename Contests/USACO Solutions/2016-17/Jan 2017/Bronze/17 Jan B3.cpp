//#include <iostream>
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

int n, ans = 0;
char x[10][10];

int main() {
	ifstream cin ("cowtip.in");
	ofstream cout ("cowtip.out");
	cin >> n;
	F0R(i,n) F0R(j,n) cin >> x[i][j];
	for (int i = n-1; i >= 0; --i)
		for (int j = n-1; j >= 0; --j)
			if (x[i][j] == '1') {
				ans++;
				for (int i1 = i; i1 >= 0; --i1)
					for (int j1 = j; j1 >= 0; --j1)
						x[i1][j1] = char('1'-int(x[i1][j1]-'0'));
			}
	cout << ans;
}
