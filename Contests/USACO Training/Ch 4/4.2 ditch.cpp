/*
ID: bqi3431
PROG: ditch
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

int rate[201][201], prevnode[201], flow[201];
bool visit[201];

int main() {
	//ifstream cin ("ditch.in");
	//ofstream cout ("ditch.out");
	int N,M; cin >> N >> M;
	F0R(i,N) {
		int S,E,C; cin >> S >> E >> C;
		rate[S][E] = C;
	}
	ll ans = 0;

	while (1) {
		FOR(i,1,M+1) flow[i] = visit[i] = prevnode[i] = 0;
		flow[1] = MOD;

		int maxflow, maxloc;
		while (1) {
			maxflow = 0, maxloc = -1;
			FOR(i,1,M+1) 
				if (!visit[i] && flow[i]>maxflow) 
					maxflow = flow[i], maxloc = i;
				
			if (maxloc == -1 || maxloc == M) break;
			visit[maxloc] = 1;
			FOR(i,1,M+1) if(flow[i]<min(maxflow,rate[maxloc][i])) {
				prevnode[i] = maxloc;
				flow[i] = min(maxflow,rate[maxloc][i]);
			}
		}
		// cout << maxloc << "\n";
		if (maxloc == -1) break;
		ans = ans+flow[M];
		int curnode = M;
		while (curnode != 1) {
			int nextnode = prevnode[curnode];
			rate[nextnode][curnode] -= flow[M];
			rate[curnode][nextnode] += flow[M];
			curnode = nextnode;
		}
	}
	cout << ans;
}
