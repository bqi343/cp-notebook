/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

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

int N,W, C[18], dp[1<<18], to[1<<18], ind;

void search(int wei, int cur, int nex) {
    if (dp[cur]<dp[ind]) {
        dp[ind] = dp[cur]+1;
        to[ind] = cur;
    }
    if (nex == N) return;
    search(wei,cur,nex+1);
    if (cur&(1<<nex)) 
        if (wei+C[nex] <= W) 
            search(wei+C[nex],cur^(1<<nex),nex+1);
}

void solve() {
    F0R(i,N) if (ind&(1<<i)) {
        search(C[i],ind^(1<<i),i+1);
        break;
    }
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N >> W;
	F0R(i,N) cin >> C[i];
	
	FOR(i,1,1<<N) {
	    ind = i;
	    dp[ind] = MOD;
	    solve();
	}
	cout << dp[(1<<N)-1] << "\n";
	int c = (1<<N)-1;
	vi ans;
	while (c) {
	    F0R(i,N) if (c & (1<<i)) if ((to[c] & (1<<i)) == 0) ans.pb(i);
	    cout << ans.size() << " ";
	    for (int i: ans) cout << i+1 << " ";
	    cout << "\n";
	    ans.clear();
	    c = to[c];
	}
}
