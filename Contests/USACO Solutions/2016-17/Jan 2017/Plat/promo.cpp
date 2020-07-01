#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T> using Tree = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

const int MX = 1e5+5;
#define sz(x) (int)(x).size()

int N, a[MX], ind[MX], ans[MX], ret;
vector<int> child[MX];
Tree<int> d[MX];

void comb(int a, int b) {
	if (sz(d[a]) < sz(d[b])) d[a].swap(d[b]);
	for (int i: d[b]) d[a].insert(i);
}

void dfs(int x) {
	ind[x] = x; 
	for (int i: child[x]) {
		dfs(i);
		comb(x,i);
	}
	ans[x] = sz(d[x])-d[x].order_of_key(a[x]);
	d[x].insert(a[x]);
}

int main() {
	freopen("promote.in","r",stdin);
	freopen("promote.out","w",stdout);
	cin >> N; for (int i = 1; i <= N; ++i) cin >> a[i];
	for (int i = 2; i <= N; ++i) {
		int p; cin >> p;
		child[p].push_back(i);
	}
	dfs(1); 
	for (int i = 1; i <= N; ++i) cout << ans[i] << "\n";
}