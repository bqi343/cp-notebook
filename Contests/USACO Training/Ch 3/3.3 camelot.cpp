/*
ID: bqi3431
PROG: camelot
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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

pi king;
vector<pi> knight;
int C,R, dist[26][30][26][30]; 
int xdir[8] = {2,1,-1,-2,-2,-1,1,2}, ydir[8] = {1,2,2,1,-1,-2,-2,-1};

void fill(int i, int j) {
	queue<pi> todo;
	todo.push(mp(i,j));
	dist[i][j][i][j] = 0;
	while (todo.size()) {
		pi x = todo.front();
		todo.pop();
		F0R(z,8) {
			int newf = x.f+xdir[z], news = x.s+ydir[z];
			if (newf<0 || newf >= C || news<0 || news>=R) continue;
			if (dist[i][j][newf][news] != MOD) continue;
			dist[i][j][newf][news] = dist[i][j][x.f][x.s]+1;
			todo.push(mp(newf,news));
		}
	}
}

int main() {
	//ifstream cin ("camelot.in");
	//ofstream cout ("camelot.out");
	F0R(a,26) F0R(b,30) F0R(c,26) F0R(d,30) dist[a][b][c][d] = MOD;
	cin >> R >> C;
	char x;
	int x1;
	cin >> x >> x1;
	king = mp(x-'A',x1-1);
	while (cin >> x) {
		cin >> x1;
		knight.pb(mp(x-'A',x1-1));
	}
	F0R(i,C) F0R(j,R) fill(i,j);
	ll fin = MOD;
	F0R(i,C) F0R(j,R) {
		ll ans = 0, ans1 = max(abs(i-king.f),abs(j-king.s));
		for (auto a: knight) ans += dist[i][j][a.f][a.s];
		// cout << i << " " << j << " " << " " << ans << "\n";
		for (auto a: knight) FOR(i1,-2,3) FOR(j1,-2,3) {
			int newf = king.f+i1, news = king.s+j1;
			if (newf<0 || newf >= C || news<0 || news>=R) continue;
			ll temp = dist[a.f][a.s][newf][news]+dist[i][j][newf][news]
				+max(abs(i1),abs(j1))-dist[i][j][a.f][a.s];
			ans1 = min(ans1,temp);
		}
		
		ans += ans1;
		fin = min(fin,ans);
	}
	if (knight.size() == 0) fin = 0;
	cout << fin << "\n";
}
