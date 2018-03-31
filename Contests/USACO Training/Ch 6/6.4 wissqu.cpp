/*
ID: bqi3431
PROG: wissqu
LANG: C++11
*/

#include<iostream>
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
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

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

int lef[5] = {3,3,3,4,3}, cur[4][4], tot = 0;
bool done[4][4], fil[16];
string ans[16];

bool valid(int x, int y) {
	if (x<0 || x>3) return 0;
	if (y<0 || y>3) return 0;
	return 1;
}

bool posi(int i, int j, int k) {
	if (done[i][j]) return 0;
	FOR(xdir,-1,2) FOR(ydir,-1,2) {
		int nx = i+xdir, ny = j+ydir;
		if (!valid(nx,ny)) continue;
		if (k == cur[nx][ny]) return 0;
	}
	return 1;
}

bool dfs(int num, int let, int x, int y) {
	// cout << num << " " << let << " " << x << " " << y << "\n";
	bool ret = 0;
	int let1 = cur[x][y];
	cur[x][y] = let; done[x][y] = 1; lef[let] --;
	if (num == 15) {
		tot++;
		if (!fil[num]) {
			ans[num] = char('A'+let);
			ans[num] += " ";
			ans[num] += char('1'+x);
			ans[num] += " ";
			ans[num] += char('1'+y);
			fil[num] = 1;
		}
		ret = 1;
	}
	F0R(k,5) if (lef[k]) F0R(i,4) F0R(j,4) {
		if (posi(i,j,k)) {
			bool temp = dfs(num+1, k, i, j);
			if(temp && !fil[num]) {
				ans[num] = char('A'+let);
				ans[num] += " ";
				ans[num] += char('1'+x);
				ans[num] += " ";
				ans[num] += char('1'+y);
				fil[num] = 1;
				ret = 1;
			}
		}
	}
	cur[x][y] = let1; done[x][y] = 0; lef[let] ++;
	return ret;
}

int main() {
	F0R(i,4) {
		F0R(j,4) {
			char x; cin >> x;
			cur[i][j] = x-'A';
		}
	}
	F0R(i,4) F0R(j,4) 
		if (posi(i,j,3)) dfs(0,3,i,j);
	F0R(i,16) cout << ans[i] << "\n";
	cout << tot << "\n";
}
