#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define mp make_pair
#define pb push_back
#define pi pair <int, int>
#define vi vector<int>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define FORd(i, a, b) for (int i=a-1; i>=b; i--)
#define F0Rd(i, a) for (int i=a-1; i>=0; i--)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second
#define be begin
#define e end
#define lb lower_bound
#define ub upper_bound
 
const int MOD = 1000000007;
const int MAX = 50001;

int N,K,x,y, depth[MAX], parents[MAX][16], dfs1[MAX], ans=0;
vi adjacent[MAX];

int parent(int node, int level) {
	F0Rd(i,16) {
		if (level & (1 << i)) {
			node = parents[node][i];
		}
	}
	return node;
}

int LCA(int a, int b) {
	if (depth[a] < depth[b]) b = parent(b,depth[b]-depth[a]);
	if (depth[a] > depth[b]) a = parent(a,depth[a]-depth[b]);
	if (a == b) return a;
	F0Rd(i,16) {
		if (parents[a][i] != parents[b][i]) {
			a = parents[a][i];
			b = parents[b][i];
		}
	}
	return parents[a][0];
}

int find_ans(int prev, int node) {
	int c = 0;
	for (int i: adjacent[node]) if (i != prev) c += find_ans(node,i);
	c += dfs1[node];
	ans = max(c,ans);
	return c;
}

void dfs(int prev, int node, int cdepth) {
	depth[node] = cdepth;
	parents[node][0] = prev;
	FOR(i,1,16) parents[node][i] = parents[parents[node][i-1]][i-1];
	for (int i: adjacent[node]) if (i != prev) dfs(node,i,cdepth+1);
}

int main() {
	scanf("%d%d",&N,&K);
	F0R(i,N-1) {
		scanf("%d%d",&x,&y);
		adjacent[x].pb(y);
		adjacent[y].pb(x);
	}
	dfs(0,1,1);
	F0R(i,K) {
		scanf("%d%d",&x,&y);
		int k = LCA(x,y);
		dfs1[x] ++, dfs1[y]++;
		dfs1[k] --, dfs1[parents[k][0]] --;
	}
	find_ans(0,1);
	cout << ans;
	return 0;
}
