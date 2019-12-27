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
const int MX = 100000;

int a,d;
ll tot = 0;
vector<pii> A,D;

double get(vector<pii>& z, double x) {
    double cur = 0;
    for (auto a: z) {
        double Z = min(x,(double)a.s);
        cur += Z*a.f/a.s;
        x -= Z;
    }
    return cur;
}

double test(double x) {
    return get(A,x)+get(D,x);
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> a >> d;
	F0R(i,a) {
	    int h,t; cin >> h >> t;
	    A.pb({h,t});
	    tot += h;
	}
	F0R(i,d) {
	    int h,t; cin >> h >> t;
	    D.pb({h,t});
	}
	double lo = 0, hi = 500000;
	F0R(i,100) {
	    double mid = (lo+hi)/2;
	    if (test(mid) >= tot) hi = mid;
	    else lo = mid;
	}
	cout << fixed << setprecision(6) << lo;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!