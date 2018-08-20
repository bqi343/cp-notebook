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

int N,T, cost[100][100], MOD = 1000000007;
int best[100][100][3], xdir[4] = {1,0,-1,0}, ydir[4] = {0,1,0,-1};
priority_queue<pair<pi,pi>> todo;

int main() {
	ifstream cin ("visitfj.in");
	ofstream cout ("visitfj.out");
	cin >> N >> T;
	F0R(i,N) F0R(j,N) F0R(k,3) best[i][j][k] = MOD;
	F0R(i,N) F0R(j,N) cin >> cost[i][j];
	todo.push({{0,0},{0,0}});
	while (todo.size()) {
		auto a = todo.top();
		todo.pop();
		a.f.f = -a.f.f;
		if (a.s.f == N-1 && a.s.s == N-1) {
			cout << a.f.f;
			return 0;
		}
		if (best[a.s.f][a.s.s][a.f.s] != MOD) continue;
		best[a.s.f][a.s.s][a.f.s] = a.f.f;
		a.f.s = (a.f.s+1) % 3;
		F0R(i,4) {
			int nx = a.s.f+xdir[i], ny = a.s.s+ydir[i];
			if (nx >= 0 && nx < N && ny >= 0 && ny < N && best[nx][ny][a.f.s] == MOD) {
				if (a.f.s == 0) todo.push({{-(a.f.f+T+cost[nx][ny]),a.f.s},{nx,ny}});
				else todo.push({{-(a.f.f+T),a.f.s},{nx,ny}});
			}
		}
	}
}
