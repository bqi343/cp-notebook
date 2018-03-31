// #include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

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

int M, N, T, grid[500][500], query[500][500]; 
ll ans;
vector<pair<int,pair<pi,pi>>> edge;
pi comp[500][500];
vector<pi> mem[500][500];

ifstream cin ("skilevel.in");
ofstream cout ("skilevel.out");

pi getpar(pi a) {
	pi p = comp[a.f][a.s];
	if (comp[p.f][p.s] == p) return p;
	return getpar(p);
}

void unite(int wei, pi a, pi b) {
	a = getpar(a), b = getpar(b);
	if (a == b) return;
	
	if (mem[a.f][a.s].size()+mem[b.f][b.s].size() >= T) {
		if (mem[a.f][a.s].size() < T) for (auto i: mem[a.f][a.s]) query[i.f][i.s] = wei;
		if (mem[b.f][b.s].size() < T) for (auto i: mem[b.f][b.s]) query[i.f][i.s] = wei;
	}
	if (mem[a.f][a.s].size() < mem[b.f][b.s].size()) swap(a,b);
	for (auto i: mem[b.f][b.s]) mem[a.f][a.s].pb(i);
	comp[b.f][b.s] = a;
}

int main() {
	cin >> M >> N >> T;
	F0R(i,M) F0R(j,N) cin >> grid[i][j];
	
	F0R(i,M) F0R(j,N) comp[i][j] = {i,j}, mem[i][j].pb({i,j});
	F0R(i,M-1) F0R(j,N) edge.pb({abs(grid[i][j]-grid[i+1][j]),{{i,j},{i+1,j}}});
	F0R(i,M) F0R(j,N-1) edge.pb({abs(grid[i][j]-grid[i][j+1]),{{i,j},{i,j+1}}});
	sort(edge.begin(),edge.end());
	
	for (auto a: edge) unite(a.f,a.s.f,a.s.s);
	F0R(i,M) F0R(j,N) {
		int x; cin >> x;
		if (x) ans += query[i][j];
	}
	cout << ans;
}
