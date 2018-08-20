#include <iostream>
#include <fstream>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;

#define F0R(i, a) for (int i=0; i<a; i++)

ll ans = (ll)1000000000000000, N;
int x[100001], y[100001], m[100001], b[100001];

void solve() {
	F0R(i,N) m[x[i]] = i;
	tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> s;
	ll cur = N*(N-1)/2;
	F0R(i,N) {
		b[i] = m[y[i]];
		cur -= s.order_of_key(b[i]);
		s.insert(b[i]);
	}
	for (int i = N-1; i >= 0; --i) {
		ans = min(ans,cur);
		cur += (2*b[i]+1-N);
	}
}

int main() {
	// ifstream cin ("mincross.in");
	// ofstream cout ("mincross.out");
	cin >> N; 
	F0R(i,N) cin >> x[i];
	F0R(i,N) cin >> y[i];
	solve(), swap(x,y), solve();
	cout << ans;
}