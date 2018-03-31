/*
ID: bqi3431
PROG: stall4
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

int rate[402][402], prevnode[402], flow[402];
bool visit[402];

int main() {
	//ifstream cin ("ditch.in");
	//ofstream cout ("ditch.out");
	int N,M; cin >> N >> M;
	FOR(i,1,N+1) rate[0][i] = 1;
	FOR(i,N+1,N+M+1) rate[i][N+M+1] = 1;
	F0R(i,N) {
		int S; cin >> S;
		F0R(j,S) {
			int t; cin >> t;
			rate[i+1][t+N] = 1;
		}
	}
	ll ans = 0;

	while (1) {
		F0R(i,N+M+2) flow[i] = visit[i] = prevnode[i] = 0;
		flow[0] = MOD;

		int maxflow, maxloc;
		while (1) {
			maxflow = 0, maxloc = -1;
			F0R(i,N+M+2) 
				if (!visit[i] && flow[i]>maxflow) 
					maxflow = flow[i], maxloc = i;
			
			// cout << maxflow << " " << maxloc << "\n";
			if (maxloc == -1 || maxloc == N+M+1) break;
			visit[maxloc] = 1;
			F0R(i,N+M+2) if(flow[i]<min(maxflow,rate[maxloc][i])) {
				prevnode[i] = maxloc;
				flow[i] = min(maxflow,rate[maxloc][i]);
			}
		}
		// cout << flow[N+M+1] << "\n";
		// cout << maxloc << "\n";
		if (maxloc == -1) break;
		ans = ans+flow[N+M+1];
		int curnode = N+M+1;
		while (curnode != 0) {
			int nextnode = prevnode[curnode];
			rate[nextnode][curnode] -= flow[N+M+1];
			rate[curnode][nextnode] += flow[N+M+1];
			curnode = nextnode;
		}
	}
	cout << ans << "\n";
}
