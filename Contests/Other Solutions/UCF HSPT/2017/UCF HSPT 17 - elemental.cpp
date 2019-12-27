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

set<string> m;
bitset<1001> ok;
string s;

int k;

bool test(string z) {
    F0R(i,z.length()+1) ok[i] = 0;
    ok[0] = 1;
    FOR(i,1,z.length()+1) FOR(j,1,4) if (j <= i && ok[i-j] && m.count(z.substr(i-j,j))) ok[i] = 1;
    return ok[z.length()];
}

void solve() {
    m.clear();
    F0R(i,k) {
        string t; cin >> t;
        m.insert(t);
    }
    
    bool ans = 1;
    cin >> s; 
    ans &= test(s);
    
    while (cin.peek() != '\r' && cin.peek() != '\n') {
        cin >> s; 
        ans &= test(s);
    }
    if (ans == 0) cout << "Not ";
    cout << "Elemental\n";
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);

	FOR(i,1,MOD) {
	    cin >> k;
	    if (k == 0) exit(0);
	    cout << "Phrase #" << i << ": ";
	    solve();
	    cout << "\n";
	}
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
