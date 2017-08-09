/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
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

priority_queue<pii,vector<pii>,greater<pii>> q;
int dist[100];
vector<pii> adj[100];

int main() {
	F0R(i,100) F0R(j,100) if (rand() % 10 == 0) adj[i].pb({j,rand() % 10+1});
	fill_n(dist,100,MOD); dist[0] = 0; 
	
	q.push({0,0});
	while (q.size()) {
		pii x = q.top(); q.pop();
		if (dist[x.s] < x.f) continue;
		for (pii y: adj[x.s]) if (x.f+y.s < dist[y.f]) {
			dist[y.f] = x.f+y.s;
			q.push({dist[y.f],y.f});
		}
	}
	
	F0R(i,100) cout << dist[i] << "\n";
}