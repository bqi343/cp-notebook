#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

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
const double PI = 4*atan(1);
const ll INF = 1e18;

ll n, N, ans;
vector<pl> z;

ll po(ll b, ll p) {
    return p == 0 ? 1 : po(b*b%MOD,p/2)*(p&1?b:1)%MOD;
}

void solve(int cind, ll num, ll ret) {
    if (cind == sz(z)) {
        if (num != n) {
            ans += ((ret%MOD)*po(2,num));
            ans %= MOD;
        }
        return;
    }
    ll cur = 1;
    F0R(i,z[cind].s+1) {
        ll cret = ret/cur;
        if (i != z[cind].s) cret -= ret/cur/z[cind].f;
        solve(cind+1,num*cur,cret);
        cur *= z[cind].f;
    }
}

int main() {
    freopen("gymnasts.in","r",stdin);
    freopen("gymnasts.out","w",stdout);
    
    cin >> n; N = n;
    for (ll i = 2; i*i <= N; ++i) if (N % i == 0) {
        int t = 0; 
        while (N % i == 0) {
            t ++;
            N /= i;
        }
        z.pb({i,t});
    }
    if (N > 1) z.pb({N,1});
    
    solve(0,1,n);
    ans = (ans-n+2)%MOD;
    ans = (ans+MOD)%MOD;
    cout << ans;
}

// read the question correctly (is y a vowel?)
// look out for special cases (n=1?) and overflow (ll vs int?)
