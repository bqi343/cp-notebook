/*
ID: bqi3431
PROG: fence6
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

map<set<int>,int> vertex;
int dist[101][101], N, nex=1;

int dijkstra(int start, int end) {
	int best[101];
	FOR(i,1,nex) best[i] = MOD;
	priority_queue<pi> todo;
	todo.push(mp(0,start));
	while (todo.size()) {
		pi top = todo.top(); todo.pop();
		if (best[top.s] != MOD) continue;
		best[top.s] = -top.f;
		if (top.s == end) return best[top.s];
		FOR(i,1,nex) if (dist[top.s][i] != MOD && best[i] == MOD) 
			todo.push(mp(top.f-dist[top.s][i],i));
	}
}

int main() {
	//ifstream cin ("fence6.in");
	//ofstream cout ("fence6.out");
	cin >> N;
	F0R(i,101) F0R(j,101) dist[i][j] = MOD;
	F0R(i,N) {
		int s,l,n1,n2; cin >> s >> l >> n1 >> n2;
		set<int> f1,f2;
		f1.insert(s), f2.insert(s);
		F0R(i,n1) {
			int t; cin >> t;
			f1.insert(t);
		}
		F0R(i,n2) {
			int t; cin >> t;
			f2.insert(t);
		}
		if (vertex.find(f1) == vertex.end()) vertex[f1] = nex++;
		if (vertex.find(f2) == vertex.end()) vertex[f2] = nex++;
		dist[vertex[f1]][vertex[f2]] = dist[vertex[f2]][vertex[f1]] = l;
	}
	/*FOR(i,1,nex) {
		FOR(j,1,nex) cout << dist[i][j] << " ";
		cout << "\n";
	}*/
	int ans = MOD;
	FOR(i,1,nex) FOR(j,i+1,nex) if (dist[i][j] != MOD) {
		int temp = dist[i][j];
		dist[i][j] = dist[j][i] = MOD;
		ans = min(ans,dijkstra(i,j)+temp);
		//cout << dijkstra(i,j) << " " << temp << "\n";
		dist[i][j] = dist[j][i] = temp;
	}
	cout << ans;
}
