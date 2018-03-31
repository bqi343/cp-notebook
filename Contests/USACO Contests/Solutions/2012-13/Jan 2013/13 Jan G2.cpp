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
#include<queue>

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

ifstream cin ("island.in");
ofstream cout ("island.out");

int R,C,num=0,xdir[4] = {1,0,-1,0}, ydir[4] = {0,1,0,-1};
int dist[15][15], cur[50][50], dp[1<<15][15];
char grid[50][50];

void fill(int x, int y) {
	if (x<0 || x >= R || y<0 || y >= C) return;
	if (grid[x][y] != 'X') return;
	grid[x][y] = 'a'+num;
	F0R(i,4) fill(x+xdir[i],y+ydir[i]);
}

void getdist(int col) {
	F0R(i,R) F0R(j,C) cur[i][j] = MOD;
	
	priority_queue<pair<int,pi>> todo;
	F0R(i,R) F0R(j,C) if (grid[i][j] == ('a'+col)) {
		cur[i][j] = 0;
		todo.push({0,{i,j}});
	}
	while (todo.size()) {
		auto a = todo.top(); todo.pop();
		if (-a.f > cur[a.s.f][a.s.s]) continue;
		F0R(i,4) {
			int nx = a.s.f+xdir[i], ny = a.s.s+ydir[i];
			if (nx<0 || nx >= R || ny<0 || ny >= C) continue;
			if (grid[nx][ny] == '.') continue;
			int s = -a.f;
			if (grid[nx][ny] == 'S') s++;
			if (s >= cur[nx][ny]) continue;
			cur[nx][ny] = s;
			todo.push({-s,{nx,ny}});
		}
	}
	F0R(i,R) F0R(j,C) if ('a' <= grid[i][j] && grid[i][j] <= 'z') 
		dist[col][grid[i][j]-'a'] = cur[i][j];
	
}

int main() {
	cin >> R >> C;
	F0R(i,R) F0R(j,C) cin >> grid[i][j];
	F0R(i,R) F0R(j,C) if (grid[i][j] == 'X') {
		fill(i,j);
		num ++;
	}
	F0R(i,num) getdist(i);
	F0R(i,1<<num) F0R(j,num) dp[i][j] = MOD;
	F0R(i,1<<num) F0R(j,num) if (i & (1<<j)) {
		if (i == (1<<j)) dp[i][j] = 0;
		F0R(k,num) if ((i & (1<<k)) == 0) 
			dp[i|(1<<k)][k] = min(dp[i|(1<<k)][k],dp[i][j]+dist[j][k]);
	}
	int ans = MOD;
	F0R(i,num) ans = min(ans,dp[(1<<num)-1][i]);
	cout << ans;
}
