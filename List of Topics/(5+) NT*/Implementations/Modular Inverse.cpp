// http://blog.ruofeidu.com/treap-in-45-lines-of-c/
// https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/Treap.h

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

ll inv (ll b) { // MOD is prime
    ll ans = 1, p = MOD-2;
    while (p) {
        if (p&1) ans = ans*b % MOD;
        p >>= 1;
        b = b*b % MOD;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout << inv(7) << " " << 7*inv(7) % MOD << "\n";
}

// read!
// ll vs. int!
