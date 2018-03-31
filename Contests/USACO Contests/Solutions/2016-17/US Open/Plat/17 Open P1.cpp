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

int num[1000001], lowx[1000001], highx[1000001], lowy[1000001], highy[1000001], n, ans = 0;
int grid[1000][1000], numc = 0;
bool posi[1000001];

int main() {
	ifstream cin ("art.in");
	ofstream cout ("art.out");
	cin >> n;
	FOR(i,1,n*n+1) lowx[i] = MOD, lowy[i] = MOD, highx[i] = -1, highy[i] = -1, posi[i] = 1;
	F0R(i,n) F0R(j,n) {
		cin >> grid[i][j];
		int z = grid[i][j];
		if (z) {
			if (num[z] == 0) numc ++;
			num[z] ++;
			lowx[z] = min(lowx[z],i);
			highx[z] = max(lowx[z],i);
			lowy[z] = min(lowy[z],j);
			highy[z] = max(highy[z],j);
		}
	}
	FOR(i,1,n*n+1) if (lowx[i] != MOD) 
		FOR(i1,lowx[i],highx[i]+1)
			FOR(i2,lowy[i],highy[i]+1)
				if (grid[i1][i2] != i) posi[grid[i1][i2]] = 0;
				
	int ans = 0;
	FOR(i,1,n*n+1) if (posi[i]) ans++;
	if (numc == 1) ans--;
	cout << ans;
}
