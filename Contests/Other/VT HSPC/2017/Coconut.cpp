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

int s,n;
vector<pii> v;
int t;

void sim() {
    t = (t+s-1)%v.size();
    if (v[t].f == 0) {
        vector<pii> v1;
        F0R(i,t) v1.pb(v[i]);
        v1.pb({1,v[t].s});
        v1.pb({1,v[t].s});
        FOR(i,t+1,v.size()) v1.pb(v[i]);
        swap(v,v1);
    } else if (v[t].f == 1) {
        v[t].f = 2;
        t++;
    } else v.erase(v.begin()+t);
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> s >> n;
    FOR(i,1,n+1) v.pb({0,i});
    while (v.size() > 1) sim();
    cout << v[0].s;
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!