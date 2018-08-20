#include <iostream>
#include <fstream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds; 
using namespace std;

typedef pair<int,int> pi;
typedef tree<pi,null_type,less<pi>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i,a,b) for (int i=a; i<b; i++)

// ifstream cin ("promote.in");
// ofstream cout ("promote.out");

int N, prof[100001], loc[100001], ans[100001];
vector<int> child[100001];
ordered_set todo[100001];

void dfs(int nod) {
	int mx = nod;
	for (int i: child[nod]) {
		dfs(i);
		if (todo[loc[i]].size()>todo[mx].size()) mx = loc[i];
	}
	loc[nod] = mx;
	for (int i: child[nod]) if (loc[i] != mx) 
		for (auto j: todo[loc[i]]) todo[mx].insert({j.first,todo[mx].size()});
	ans[nod] = todo[mx].size()-todo[mx].order_of_key({prof[nod],todo[mx].size()});
	todo[mx].insert({prof[nod],todo[mx].size()});
}

int main() {
    cin >> N;
    FOR(i,1,N+1) cin >> prof[i];
    FOR(i,2,N+1) {
    	int p; cin >> p;
    	child[p].push_back(i);
    }
    FOR(i,1,N+1) loc[i] = i; 
    dfs(1);
    FOR(i,1,N+1) cout << ans[i] << "\n";
}
