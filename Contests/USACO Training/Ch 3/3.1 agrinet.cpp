/*
ID: bqi3431
PROG: agrinet
LANG: C++11
*/

//#include <iostream>
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

ifstream cin ("agrinet.in");
ofstream cout ("agrinet.out");

vector<pair<int,pi>> edge;
int par[100],ans=0;

int getpar(int node) {
	if (par[par[node]] == par[node]) return par[node];
	return par[node] = getpar(par[node]);
}

void merge(int a, int b, int c) {
	if ((a = getpar(a)) == (b = getpar(b))) return;
	if(a>b) swap(a,b);
	ans += c;
	par[b]=a;
}

int main() {
	int N; cin >> N;
	F0R(i,N) par[i] = i;
	F0R(i,N) F0R(j,N) {
		int e; cin >> e;
		if (i<j) edge.pb(mp(e,mp(i,j)));
	}
	sort(edge.begin(),edge.end());
	for (auto a: edge) merge(a.s.f,a.s.s,a.f);
	cout << ans << "\n";
}
