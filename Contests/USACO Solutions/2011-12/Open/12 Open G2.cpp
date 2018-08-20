/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<ll, ll> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define pf push_front
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
double PI = 4*atan(1);

// maximum with deque
deque<pair<ll,pair<ll,pair<ll,ll>>>> t;
ll H[100001], W[100001],dp[100001],N,L, cum[100001];
multiset<ll> best;

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> L;
	FOR(i,1,N+1) {
	    cin >> H[i] >> W[i];
	    cum[i] = cum[i-1]+W[i];
	}
	int pre = 0;
	FOR(i,1,N+1) {
	    // modify the back
	    pair<ll,pair<ll,pi>> a = {dp[i-1]+H[i],{H[i],{i-1,i-1}}};
	    while (t.size() > 0 && t.back().s.f <= a.s.f) {
	        pair<int,pair<int,pi>> b = t.back(); t.pop_back();
	        best.erase(best.find(b.f));
	        a.s.s.f = b.s.s.f;
	        a.f = dp[a.s.s.f]+H[i];
	    }
	    t.pb(a);
	    best.insert(a.f);
	    
	    // now modify the front
	    while (cum[i]-cum[pre] > L) pre++;
	    while (t.front().s.s.f < pre) {
	        best.erase(best.find(t.front().f));
	        t.front().s.s.f = pre;
	        if (t.front().s.s.f > t.front().s.s.s) t.pop_front();
	        else {
	            t.front().f = t.front().s.f+dp[pre];
	            best.insert(t.front().f);
	        }
	    }
	    
	    dp[i] = *best.begin();
	}
	cout << dp[N];
}
