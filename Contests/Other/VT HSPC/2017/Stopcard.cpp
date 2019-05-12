#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
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
const int MX = 70;

int n,c, a[MX];
double prob[MX], ans;

double comb(int x, int y) {
    if (y > x) return 0;
    double ex = 1;
    F0R(i,y) {
        ex *= x-i;
        ex /= i+1;
    }
    return ex;
}

double getex(int ind) {
    double tot = 0, res = 0;
    F0R(i,n) {
        tot += comb(i,ind-1);
        res += comb(i,ind-1)*a[i];
    }
    return res/tot;
}

void test(int ind) {
    if (ind == n) {
        double x = 0; F0R(i,n) x += a[i];
        ans += prob[ind]*x/n;
    } else ans += (prob[ind]-prob[ind+1])*getex(ind);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n >> c; // first draw c cards
	
	F0R(i,n) cin >> a[i];
	sort(a,a+n);
	
	prob[c+1] = 1;
	FOR(i,c+1,n) {
	    prob[i+1] = (i-1)*prob[i]/i;
	}
	FOR(i,c+1,n+1) test(i);
	cout << fixed << setprecision(6) << ans;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!