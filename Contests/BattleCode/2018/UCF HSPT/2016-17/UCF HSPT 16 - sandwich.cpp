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

const int MOD = 1000000007;

ll n,m, ans[12], ok[1000000];
ll po10[13];

int len(ll x) {
    ll t = 10, co = 1;
    while (t <= x) t *= 10, co++;
    return co;
} // OK

void gen() {
    po10[0] = 1;
    FOR(i,1,13) po10[i] = 10*po10[i-1];
    FOR(i,1,1000000) {
        string s = to_string(i);
        ok[i] = 1;
        FOR(j,1,s.length()) if (s.substr(0,j) == s.substr(s.length()-j,j)) ok[i] = 0;
    } // OK
    FOR(i,1,12) {
        int t = 1; F0R(j,i/2) t *= 10;
        FOR(j,1,t) if (ok[j]) ans[i] += pow(10,i-2*len(j));
    }
}

ll test(ll x, ll j, int le) {
    //cout << x << " " << j << " " << le << "\n";
    if (x/po10[le-len(j)] < j) return 0;
    if (x/po10[le-len(j)] == j) {
        ll nx = x-j*po10[le-len(j)]-j;
        //cout << nx << "\n";
        if (nx < 0) return 0;
        return nx/po10[len(j)]+1;
    } 
    return po10[le-2*len(j)];
}

ll solve(ll x) {
    string s = to_string(x);
    ll fin = 0;
    FOR(i,1,s.length()) fin += ans[i];
    int t = 1; F0R(j,s.length()/2) t *= 10;
    FOR(j,1,t) if (ok[j]) {
        fin += test(x,j,s.length());
    }
    return fin;
}

int main() {
    gen();
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	FOR(i,1,n+1) {
	    ll x; cin >> x;
	    if (x == 1e12) x--;
	    cout << "Number #" << i << ": " << "There are " << solve(x) << " sandwich numbers that meet our criteria.\n";
	}
}

// read!
// ll vs. int!
