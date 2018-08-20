#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef tree<pi,null_type,less<pi>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

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

int N,X, num[100000], ad = 0, lst = 0; // how many subsequences at least 0
ordered_set z;

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> X;
	F0R(i,N) {
	    int h; cin >> h;
	    if (h < X) num[i] = -1;
	    else num[i] = 1;
	}
	z.insert({0,0});
	
	ll ans = 0;
	F0R(i,N) {
	    ans += (z.size()-z.order_of_key({-ad-num[i],-MOD}));
	    ad += num[i];
	    z.insert({-ad,i+1});
	}
	cout << ans;
}
