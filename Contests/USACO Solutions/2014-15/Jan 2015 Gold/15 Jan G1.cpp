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

pi rec[1001][1001], ans = {0,0};
set<int> todo;

int main() {
	ifstream cin ("cowrect.in");
	ofstream cout ("cowrect.out");
	
	int N; cin >> N;
	F0R(i,N) {
		int x,y; char c; cin >> x >> y >> c;
		if (c == 'H') rec[x][y].f ++;
		else rec[x][y].s ++;
		todo.insert(x);
	}
	
	FOR(i,1,1001) FOR(j,1,1001) rec[i][j].f += rec[i-1][j].f, rec[i][j].s += rec[i-1][j].s;
	for (int a: todo) for (int b: todo) if (a <= b) {
		int ccow = 0, cy = 1;
		FOR(i,1,1001) {
			int h = rec[b][i].f, g = rec[b][i].s;
			if (a>0) h -= rec[a-1][i].f, g -= rec[a-1][i].s;
			if (g) { cy = i+1; ccow = 0; continue; }
			ccow += h;
			if (ccow > ans.f) ans = {ccow,(b-a)*(i-cy)};
			else if (ccow == ans.f)  ans.s = min(ans.s,(b-a)*(i-cy));
			if (ccow == 0) cy = i+1;
		}
	}
	cout << ans.f << "\n" << ans.s;
}
