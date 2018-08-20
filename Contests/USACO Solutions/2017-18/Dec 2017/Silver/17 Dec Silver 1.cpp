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
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;

typedef long double ld;

int sum = 0, h[100000];
multiset<int> cur;
int N;
pair<ld,vi> bes;

int main() {
    freopen("homework.in","r",stdin);
    freopen("homework.out","w",stdout);
    
	cin >> N;
	F0R(i,N) {
	    cin >> h[i];
	    sum += h[i];
	    cur.insert(h[i]);
	}
	F0R(i,N-2) {
	    cur.erase(cur.find(h[i])); sum -= h[i];
	    ld t = (ld)(sum-*cur.begin())/(N-i-2);
	    if (t > bes.f) {
	        bes.f = t;
	        bes.s.clear();
	        bes.s.pb(i+1);
	    } else if (t == bes.f) {
	        bes.s.pb(i+1);
	    }
	}
	F0R(i,sz(bes.s)) {
	    if (i) cout << "\n";
	    cout << bes.s[i];
	}
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
