/*
ID: bqi3431
PROG: holstein
LANG: C++11 
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
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
const int MX = 100001;

int V,G,bes = (1<<16)-1, req[25], val[15][25];

void search(int ind, int use) {
    bool bad = 0;
    F0R(i,V) if (req[i] > 0) bad = 1;
    if (!bad) {
        if (__builtin_popcount(use) < __builtin_popcount(bes)) bes = use;
        else if (__builtin_popcount(use) == __builtin_popcount(bes)) bes = min(bes,use);
        return;
    }
    if (ind < G) {
        search(ind+1,use);
        F0R(i,V) req[i] -= val[ind][i];
        search(ind+1,use^(1<<ind));
        F0R(i,V) req[i] += val[ind][i];
    }
}

int main() {
    freopen("holstein.in","r",stdin);
    freopen("holstein.out","w",stdout);
    
    cin >> V;
    F0R(i,V) cin >> req[i];
    cin >> G;
    F0R(i,G) F0R(j,V) cin >> val[i][j];
    
    search(0,0);
    cout << __builtin_popcount(bes);
    F0R(i,G) if (bes&(1<<i)) cout << " " << i+1;
    cout << "\n";
}

// read the question correctly (is y a vowel?)
// look out for special cases (n=1?) and overflow (ll vs int?)
