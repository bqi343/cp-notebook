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

ifstream cin ("route.in");
ofstream cout ("route.out");

ll N,M,R, dplef[40000], dpri[40000], ans = 0;
vi lef, ri;
vector<pi> path;

int main() {
	cin >> N >> M >> R; lef.resize(N), ri.resize(M); path.resize(R);
	F0R(i,N) {
		cin >> lef[i];
		dplef[i] = lef[i];
		ans = max(ans,dplef[i]);
	}
	F0R(i,M) {
		cin >> ri[i];
		dpri[i] = ri[i];
		ans = max(ans,dpri[i]);
	}
	F0R(i,R) cin >> path[i].f >> path[i].s;
	sort(path.begin(),path.end());
	reverse(path.begin(),path.end());
	for (auto a: path) {
		a.f --, a.s--;
		ll x = max(dplef[a.f],dpri[a.s]+lef[a.f]);
		ll y = max(dpri[a.s],dplef[a.f]+ri[a.s]);
		dplef[a.f] = x, dpri[a.s] = y;
		ans = max(ans,max(x,y));
	}
	cout << ans;
}
