https://open.kattis.com/problems/polygonarea

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

const int MOD = 1000000007;
const double PI = 4*atan(1);

int n;

double area(vector<pii> v) {
    double x = 0;
    F0R(i,v.size()) {
        x += v[i].f*v[(i+1)%v.size()].s;
        x -= v[(i+1)%v.size()].f*v[i].s;
    }
    return x/2;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    cout << fixed << setprecision(1);
    while (cin >> n) {
        if (n == 0) return 0;
        vector<pii> v(n); F0R(i,n) cin >> v[i].f >> v[i].s;
        double tmp = area(v);
        if (tmp < 0) cout << "CW ";
        else cout << "CCW ";
        cout << abs(tmp) << "\n";
    }
}

// read!
// ll vs. int!