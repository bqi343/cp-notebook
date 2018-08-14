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

int n;
map<string,int> m;

void solve() {
    int x; cin >> x;
    int lst,ans=0;
    F0R(i,x) {
        string s; cin >> s;
        if (i) {
            int g = m[s]-lst;
            ans += min(abs(g),min(abs(g+12),abs(g-12)));
        }
        lst = m[s];
    }
    cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	m["A"] = 0;
	m["A#"] = 1;
	m["Bb"] = 1;
	m["B"] = 2;
	m["C"] = 3;
	m["C#"] = 4;
	m["Db"] = 4;
	m["D"] = 5;
	m["D#"] = 6;
	m["Eb"] = 6;
	m["E"] = 7;
	m["F"] = 8;
	m["F#"] = 9;
	m["Gb"] = 9;
	m["G"] = 10;
	m["G#"] = 11;
	m["Ab"] = 11;
	cin >> n;
	FOR(i,1,n+1) {
	    cout << "Song #" << i << ": ";
	    solve();
	}
}

// read!
// ll vs. int!
