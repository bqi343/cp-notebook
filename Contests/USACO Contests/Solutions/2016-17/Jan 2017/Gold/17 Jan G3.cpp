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

char grid[20][20];
int dp[1600][1600], N;
int xdir[4] ={1,0,-1,0}, ydir[4] = {0,1,0,-1};
queue<pair<int,pi>> q;

int pack(pair<int,pi> a) {
	return 400*a.f+20*a.s.f+a.s.s;
}

pair<int,pi> unpack(int cur) {
	int dir = cur / 400; cur %= 400;
	int x = cur / 20;
	return {dir,{cur/20,cur%20}};
}

bool valid (int x, int y) {
	if (x<0 || x>=N) return 0;
	if (y<0 || y>=N) return 0;
	if (grid[x][y] == 'H') return 0;
	return 1;
}

int main() {
	ifstream cin ("cownav.in");
	ofstream cout ("cownav.out");
	cin >> N;
	for (int i = N-1; i >= 0; --i) F0R(j,N) cin >> grid[j][i];
	q.push({0,{pack({0,{0,0}}),pack({1,{0,0}})}});
	while (1) {
		auto a = q.front(); q.pop();
		dp[a.s.f][a.s.s] = -a.f;
		auto b1 = unpack(a.s.f), b2 = unpack(a.s.s);
		
		if (b1.s.f == N-1 && b1.s.s == N-1 && b2.s.f == N-1 && b2.s.s == N-1) {
			cout << -a.f;
			return 0;
		}
		
		auto c1 = b1, c2 = b2;
		c1.f = (c1.f+1)%4, c2.f = (c2.f+1)%4;
		if (dp[pack(c1)][pack(c2)] == 0) {
			dp[pack(c1)][pack(c2)] = -1;
			q.push({a.f-1,{pack(c1),pack(c2)}});
		}
		c1.f = (b1.f+3)%4, c2.f = (b2.f+3)%4;
		if (dp[pack(c1)][pack(c2)] == 0) {
			dp[pack(c1)][pack(c2)] = -1;
			q.push({a.f-1,{pack(c1),pack(c2)}});
		}
		c1.f = b1.f, c2.f = b2.f;
		if (c1.s != mp(N-1,N-1) && valid(c1.s.f+xdir[c1.f],c1.s.s+ydir[c1.f]))
			c1.s = {c1.s.f+xdir[c1.f],c1.s.s+ydir[c1.f]};
		if (c2.s != mp(N-1,N-1) && valid(c2.s.f+xdir[c2.f],c2.s.s+ydir[c2.f]))
			c2.s = {c2.s.f+xdir[c2.f],c2.s.s+ydir[c2.f]};
		if (dp[pack(c1)][pack(c2)] == 0) {
			dp[pack(c1)][pack(c2)] = -1;
			q.push({a.f-1,{pack(c1),pack(c2)}});
		}
	}
}
