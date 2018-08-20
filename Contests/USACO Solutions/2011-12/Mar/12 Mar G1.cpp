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
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
double PI = 4*atan(1);

ll M,N,L,H,B, ans = 0;
vi prime[100001];

void init() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> M >> N >> L >> H >> B;
	if (L == 1) ans = ((M+1)*N+M*(N+1)) % B;
	FOR(i,2,100001) if (prime[i].size() == 0) 
	    for (int j = i; j <= 100000; j += i) 
	        prime[j].pb(i);
}

pi bad(int div, int hi) { // #, sum
    ll num = hi/div, R = div*num;
    ll sum = R*(num+1)/2 % B;
    return {num,sum};
}

pi bad(int div, int lo, int hi) {
    pi b1 = bad(div,hi);
    pi b2 = bad(div,lo-1);
    return {b1.f-b2.f,(b1.s-b2.s+B)%B};
}

void get(int ind, int lo, int hi) {
    ll tot = 0;
    F0R(i,1<<prime[ind].size()) {
        int num = 1, sum = 0;
        F0R(j,prime[ind].size()) if (i&(1<<j)) num *= prime[ind][j], sum++;
        pi t = bad(num,lo,hi);
        if (sum % 2 == 0) tot = (tot+t.f*(N+1)-t.s+B) % B;
        else {
            tot = (tot-(t.f*(N+1)-t.s)) % B;
            tot = (tot+B) % B;
        }
    }
    ans = (ans+2*(M+1-ind)*tot) % B;
}

int main() {
	init();
	for (ll i = 1; i <= M; ++i) if (i*i+N*N >= L*L && i <= H) {
	    ll lo = 1;
	    if (i <= L) lo = max(lo,(ll)ceil(sqrt(L*L-i*i)));
	    
	    ll hi = sqrt(H*H-i*i);
	    hi = min(hi,N);
	    if (lo > hi) continue;
	    
	    get(i,lo,hi);
	}
	cout << ans;
}
