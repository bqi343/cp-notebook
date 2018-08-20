#include<set>
#include<map>
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<queue>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef set<int> si;
typedef map<int,int> mii;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = b-1; i >= a; i--)
#define F0Rd(i,a) for (int i = a-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
 
const int MOD = 1000000007;
double PI = 4*atan(1);

// ifstream cin ("lasers.in");
// ofstream cout ("lasers.out");

unordered_map<int,vi> x, y;
vector<pi> places;

int dp[100002][2];

int main() {
	int N, xL,yL,xB,yB; cin >> N >> xL >> yL >> xB >> yB;
	places.pb(mp(xL,yL));
	F0R(i,N) {
		int x1, y1; cin >> x1 >> y1;
		places.pb(mp(x1,y1));
	}
	places.pb(mp(xB,yB));
	F0R(i,places.size()) {
		x[places[i].f].pb(i);
		y[places[i].s].pb(i);
	}
	
	memset(dp, -1, sizeof dp);
	queue<pi> todo;
	dp[0][0] = 0, dp[0][1] = 0;
	todo.push(mp(0,0));
	todo.push(mp(0,1));
	
	while (todo.size()) {
		pi z = todo.front(); todo.pop();
		// cout << z.f << " " << z.s << " " << dp[z.f][z.s] << "\n";
		if (z.f == places.size()-1) {
			cout << dp[z.f][z.s]-1;
			return 0;
		}
		
		if (z.s == 0) {
			for (int i: x[places[z.f].f]) if (i != z.f && dp[i][1] == -1) {
				dp[i][1] = dp[z.f][0]+1;
				todo.push(mp(i,1));
			}
		} else {
			for (int i: y[places[z.f].s]) if (i != z.f && dp[i][1] == -1) {
				dp[i][0] = dp[z.f][1]+1;
				todo.push(mp(i,0));
			}
		}
	}
	cout << -1;
}
