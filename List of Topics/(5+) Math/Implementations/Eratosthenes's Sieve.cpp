// https://open.kattis.com/problems/primesieve

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

struct Sieve {
    bitset<100000001> comp;
    Sieve() {
        FOR(i,2,10001) if (!comp[i]) {
            for (int j = i*i; j <= 100000000; j += i) comp[j] = 1;
        }
    }
    bool isprime(int x) {
        if (x == 1) return 0;
        return !comp[x];
    }
};

int n,q,ans=0;

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    Sieve s; cin >> n >> q;
    FOR(i,1,n+1) if (s.isprime(i)) ans ++;
    cout << ans << "\n";
    F0R(i,q) {
        int x; cin >> x;
        cout << s.isprime(x) << "\n";
    }
}

// read!
// ll vs. int!
