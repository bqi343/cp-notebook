/*
ID: bqi3431
PROG: snail
LANG: C++11
*/

//#include<iostream>
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

int ar[120][120],n,b;
int xdir[4] = {1,0,-1,0}, ydir[4] = {0,1,0,-1};

int valid(int x, int y) {
	if (x<0 || x>=n || y<0 || y >= n) return 1;
	if (ar[x][y] == 1) return 0;
	if (ar[x][y] == 2) return 1;
	return 2;
}

int dfs(int x, int y, int dir) {
	int x1 = x, y1 = y, ans = 0;
	/*cout << x << " " << y << " " << dir << "\n";
	F0R(i,n) {
		F0R(j,n) cout << ar[i][j];
		cout << "\n";
	}*/
	while (valid(x+xdir[dir],y+ydir[dir]) == 2) {
		x += xdir[dir], y += ydir[dir];
		ar[x][y] = 1;
		ans++;
	}
	// cout << x << " " << y << "\n";
	// cout << "\n";
	if (ans == 0) return 0;
	if (valid(x+xdir[dir],y+ydir[dir]) == 1) 
		ans += max(dfs(x,y,(dir+1)%4),dfs(x,y,(dir+3)%4));
		
	while (x != x1 || y != y1) {
		ar[x][y] = 0;
		x -= xdir[dir], y -= ydir[dir];
		// cout << "hi";
	}
	
	return ans;
}

int main() {
	ifstream cin ("snail.in");
	ofstream cout ("snail.out");
	cin >> n >> b;
	F0R(i,b) {
		char x; int y; cin >> x >> y;
		ar[x-'A'][y-1] = 2;
	} 
	ar[0][0] = 1;
	cout << 1+max(dfs(0,0,0),dfs(0,0,1)) << "\n";
}
