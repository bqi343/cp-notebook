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

ifstream cin ("rblock.in");
ofstream cout ("rblock.out");

int N,M, dist[251], least, ans;
pi pre[251];
set<pi> adj[251];
vector<pair<pi,int>> path;

int shortest() {
	dist[1] = 0;
	FOR(i,1,N+1) dist[i] = MOD;
	priority_queue<pi> todo; 
	todo.push({0,1});
	
	while (todo.size()) {
		auto a = todo.top(); todo.pop();
		a.f = -a.f;
		if (a.s == N) return a.f;
		if (a.f>dist[a.s]) continue;
		
		for (auto e: adj[a.s]) {
			if (e.s+a.f < dist[e.f]) {
				dist[e.f] = e.s+a.f;
				pre[e.f] = {a.s,e.s};
				todo.push({-(e.s+a.f),e.f});
			}
		}
	}
	return MOD;
}

int main() {
	cin >> N >> M;
	F0R(i,M) {
		int A,B,L; cin >> A >> B >> L;
		adj[A].insert({B,L});
		adj[B].insert({A,L});
	}
	least = shortest();
	int cur = N;
	while (cur != 1) {
		path.pb({{pre[cur].f,cur},pre[cur].s});
		cur = pre[cur].f;
	}
	for (auto a: path) {
		adj[a.f.f].erase({a.f.s,a.s});
		adj[a.f.f].insert({a.f.s,2*a.s});
		adj[a.f.s].erase({a.f.f,a.s});
		adj[a.f.s].insert({a.f.f,2*a.s});
		
		ans = max(ans,shortest()-least);
		
		adj[a.f.f].insert({a.f.s,a.s});
		adj[a.f.f].erase({a.f.s,2*a.s});
		adj[a.f.s].insert({a.f.f,a.s});
		adj[a.f.s].erase({a.f.f,2*a.s});
	}
	cout << ans;
}
