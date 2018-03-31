#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;

int N,G, ans;
map<int,int> hsh, ra, cur;
vector<vi> v;

void process(int i) {
	hsh[cur[v[i][1]]] ^= ra[v[i][1]];
	if (hsh[cur[v[i][1]]] == 0) hsh.erase(cur[v[i][1]]);

	cur[v[i][1]] += v[i][2];
	hsh[cur[v[i][1]]] ^= ra[v[i][1]];
}

int main() {
	freopen("measurement.in","r",stdin);
	freopen("measurement.out","w",stdout);
	cin >> N >> G;
	
	cur[0] = G;
	ra[0] = rand();
	
	F0R(i,N) {
	    int day,id,c; string change; cin >> day >> id >> change;
	    if (change[0] == '+') c = stoi(change.substr(1,sz(change)-1));
	    else c = stoi(change);

	    ra[id] = rand(), cur[id] = G;
	    v.pb({day,id,c});
	}

	for (auto a: ra) hsh[G] ^= a.s;
	sort(all(v));
	for (int i = 0; i < sz(v);) {
	    int beg = hsh.rbegin()->s;
	    int I = i;
	    while (i < sz(v) && v[i][0] == v[I][0]) process(i++);
	    int en = hsh.rbegin()->s;
	    if (beg != en) ans++;
	}
	cout << ans;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
