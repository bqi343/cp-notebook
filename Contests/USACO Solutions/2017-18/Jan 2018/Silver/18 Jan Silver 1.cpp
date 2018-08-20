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

int main() {
    // freopen("lifeguards.in","r",stdin);
    // freopen("lifeguards.out","w",stdout);
    
	int N; cin >> N;
	vector<pi> v(N);
	F0R(i,N) cin >> v[i].f >> v[i].s;
	sort(all(v)); v.pb({MOD,0});
	
	int mn = MOD, mx = 0, tot = 0;
	F0R(i,N) {
	    mn = min(mn,min(v[i].s,v[i+1].f)-max(mx,v[i].f));
	    tot += max(mx,v[i].s)-max(mx,v[i].f);
	    mx = max(mx,v[i].s);
	}
	
	cout << tot-max(mn,0);
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
