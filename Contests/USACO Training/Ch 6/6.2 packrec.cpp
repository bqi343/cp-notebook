/*
ID: bqi3431
PROG: packrec
LANG: C++11
*/

// #include <iostream>
#include <fstream>
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

int ans = MOD;
set<pi> k;
pi p[4];

void update(int l, int w) {
	if (l>w) swap(l,w);
	if (l*w < ans) ans = l*w, k.clear();
	if (l*w == ans) k.insert(mp(l,w));
}

void solve() {
	update(p[0].f+p[1].f+p[2].f+p[3].f,max(max(p[0].s,p[1].s),max(p[2].s,p[3].s)));
	update(max(p[0].s,p[1].f+p[2].f+p[3].f),p[0].f+max(p[1].s,max(p[2].s,p[3].s)));
	update(p[0].f+max(p[2].f+p[3].f,p[1].s),max(p[0].s,p[1].f+max(p[2].s,p[3].s)));
	update(max(p[0].s,max(p[1].s+p[2].s,p[3].s)),p[0].f+max(p[1].f,p[2].f)+p[3].f);
	if (p[0].s <= p[1].s && p[2].f+p[3].f <= p[0].f+p[1].f && p[2].f <= p[0].f)
		update(p[0].f+p[1].f,max(p[0].s+p[2].s,p[1].s+p[3].s));
}

int main() {
	ifstream cin ("packrec.in");
	ofstream cout ("packrec.out");
	F0R(i,4) cin >> p[i].f >> p[i].s;
	sort(p,p+4);
	F0R(z,24) {
		F0R(i,16) {
			F0R(j,4) if (i&(1<<j)) swap(p[j].f,p[j].s);
			solve();
			F0R(j,4) if (i&(1<<j)) swap(p[j].f,p[j].s);
		}
		next_permutation(p,p+4);
	}
	cout << ans << "\n";
	for (auto a: k) cout << a.f << " " << a.s << "\n";
}
