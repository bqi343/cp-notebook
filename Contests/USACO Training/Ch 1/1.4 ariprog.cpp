/*
ID: bqi3431
PROG: ariprog
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
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

bool is[125001];
	
int main() {
	//ifstream cin ("ariprog.in");
	//ofstream cout ("ariprog.out");
	int N,M; cin >> N >> M;
	F0R(i,M+1) FOR(j,i,M+1) is[i*i+j*j] = 1;
	vi posi;
	F0R(i,125001) if (is[i]) posi.pb(i);
	vector<pi> ans;
	F0R(i,posi.size()) FOR(j,i+1,posi.size()) {
		if (posi[i]+(N-1)*(posi[j]-posi[i])>2*M*M) break;
		bool x = 1;
		F0R(k,N) if (!is[posi[i]+k*(posi[j]-posi[i])]) {
			x = 0;
			break;
		}
		if (x) ans.pb(mp(posi[j]-posi[i],posi[i]));
	}
	sort(ans.begin(),ans.end());
	for (auto a: ans) cout << a.s << " " << a.f << "\n";
	if (ans.size() == 0) cout << "NONE\n";
}
