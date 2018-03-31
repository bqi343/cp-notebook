/*
ID: bqi3431
PROG: castle
LANG: C++11
*/

//#include <iostream>
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

ifstream cin ("castle.in");
ofstream cout ("castle.out");

int ar[50][50], comp[50][50], sz[2501], num, mpos;
pair<pi,int> cans;

int xdir[4] = {-1,0,1,0}, ydir[4] = {0,1,0,-1};
char dir[4] = {'W','N','E','S'};

void flood_fill(int i, int j) {
	num++;
	queue<pi> todo; todo.push(mp(i,j));
	while (todo.size()) {
		pi k = todo.front();
		todo.pop();
		if (comp[k.f][k.s]) continue;
		comp[k.f][k.s] = num, sz[num]++;
		F0R(z,4) if ((ar[k.f][k.s] & (1<<z)) == 0) if (comp[k.f+xdir[z]][k.s+ydir[z]] == 0)
			todo.push(mp(k.f+xdir[z],k.s+ydir[z]));
	}
}

int main() {
	int M,N; cin >> M >> N;
	F0Rd(j,N) F0R(i,M) cin >> ar[i][j];
	F0R(j,N) {
		F0R(i,M) {
			if (comp[i][j] == 0) flood_fill(i,j);
			//cout << comp[i][j];
		}
		//cout << "\n";
	}
	cout << num << "\n";
	int mx = 0;
	FOR(i,1,num+1) mx = max(mx,sz[i]);
	cout << mx << "\n";
	F0R(i,M) F0R(j,N) 
		F0R(z,4) if (ar[i][j] & (1<<z))
			if(i+xdir[z] >= 0 && i+xdir[z] < M)
				if (j+ydir[z] >= 0 && j+ydir[z] < N) {
					int ans = sz[comp[i+xdir[z]][j+ydir[z]]];
					if (comp[i+xdir[z]][j+ydir[z]] != comp[i][j]) ans += sz[comp[i][j]];
					if (ans>mpos) {
						cans = mp(mp(i,j),z);
						mpos = ans;
					}
				}
	cout << mpos << "\n";				
	cout << (N-cans.f.s) << " " << (cans.f.f+1) << " " << dir[cans.s] << "\n";
}
