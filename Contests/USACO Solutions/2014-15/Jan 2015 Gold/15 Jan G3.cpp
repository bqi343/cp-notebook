#include <vector>
#include <fstream>
#include <set>
#include <algorithm>
//#include <iostream>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

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

ifstream cin ("grass.in");
ofstream cout ("grass.out");

bool v[100001];
int comp[100001],sz[100001],N,M;
int to[100001], from[100001];
vi L, adj[100001], pre[100001];
set<int> adj1[100001], pre1[100001];

void visit (int u) {
	if (!v[u])	{
		v[u] = 1;
		for (int i: adj[u]) visit(i);
		L.pb(u);
	}
}

void assign(int u, int root) {
	if (comp[u] == 0) {
		comp[u] = root;
		for (int i: pre[u]) assign(i,root);
	}
}

void dfs1(int cur) {
	//cout << cur << " " << to[cur] << "\n";
	for (int i: adj1[cur]) if (to[cur]+sz[i]>to[i]) {
		to[i] = to[cur]+sz[i];
		dfs1(i);
	}
}

void dfs2(int cur) {
	//cout << "ASDF " << cur << " " << from[cur] << "\n";
	for (int i: pre1[cur]) if (from[cur]+sz[i]>from[i]) {
		from[i] = from[cur]+sz[i];
		dfs2(i);
	}
}

int main() {
	cin >> N >> M;
	F0R(i,M) {
		int x,y; cin >> x >> y;
		adj[x].pb(y);
		pre[y].pb(x);
	}
	FOR(i,1,N+1) visit(i);
	reverse(L.begin(),L.end());
	for (int i: L) assign(i,i);
	FOR(i,1,N+1) {
		for (int j: adj[i]) if (comp[i] != comp[j]) {
			adj1[comp[i]].insert(comp[j]);
			pre1[comp[j]].insert(comp[i]);
		}
		sz[comp[i]] ++;
	}
	FOR(i,1,N+1) to[i] = from[i] = -1;
	to[comp[1]] = from[comp[1]] = 0;
	dfs1(comp[1]), dfs2(comp[1]);
	int ans = sz[comp[1]];
	FOR(i,1,N+1) if (to[i]>-1) 
		for (int j: pre1[i]) if (from[j]>-1) 
			ans = max(ans,sz[comp[1]]+to[i]+from[j]); // fix
	cout << ans;
}
