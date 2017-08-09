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

int par[100], hei[100], ans = 0;
vector<pair<int,pii>> edge;

int get(int x) { // path compression
	if (par[x] != x) par[x] = get(par[x]);
	return par[x];
}

bool unite(int x, int y) { // union-by-rank
	x = get(x), y = get(y);
	if (x == y) return 0;
	if (hei[x] < hei[y]) swap(x,y);
	hei[x] = max(hei[x],hei[y]+1);
	par[y] = x;
}

int main() {
	F0R(i,100) par[i] = i, hei[i] = 1;
	F0R(i,100) FOR(j,i+1,100) if (rand() % 5 == 0) edge.pb({rand() % 100+1,{i,j}});
	
	sort(edge.begin(),edge.end());
	for (auto a: edge) if (unite(a.s.f,a.s.s)) ans += a.f;
	
	cout << ans;
}