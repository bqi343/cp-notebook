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

template<int SZ> struct Sieve {
    bitset<SZ+1> comp;
    Sieve() {
        for (int i = 2; i*i <= SZ; ++i) if (!comp[i]) {
            for (int j = i*i; j <= SZ; j += i) comp[j] = 1;
        }
    }
    bool isprime(int x) {
        if (x == 1) return 0;
        return !comp[x];
    }
};

Sieve<10000000> S;
string s;
vi tmp;

int con(vi x) {
    int t = 1, su = 0;
    F0Rd(i,x.size()) {
        su += t*x[i];
        t *= 10;
    }
    return su;
}

void solve() {
    int num = 0; tmp.clear();
    cin >> s;
    for (char c: s) tmp.pb(c-'0');
    if (!S.isprime(con(tmp))) {
        cout << "Oh no, the autobots are doomed!";
        return;
    }
    sort(tmp.begin(),tmp.end());
    do {
        if (tmp[0] != 0 && S.isprime(con(tmp))) num++;
    } while (next_permutation(tmp.begin(),tmp.end()));
    if (num >= 2) cout << "Autobots, roll out!";
    else cout << "Oh no, the autobots are doomed!";
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	int n; cin >> n;
	FOR(i,1,n+1) {
	    cout << "Battle #" << i << ": ";
	    solve();
	    cout << "\n";
	}
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!
