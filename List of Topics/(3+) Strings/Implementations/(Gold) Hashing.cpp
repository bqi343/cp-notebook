#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<ll, ll> pll;
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

pll po[200000], ipo[200000], cum[200000];
pll base = mp(948392576,573928192);

pll operator*(const pll& l, const pll& r) {
    return {l.f*r.f % MOD,l.s*r.s % MOD};
}

pll operator+(const pll& l, const pll& r) {
    return {(l.f+r.f) % MOD,(l.s+r.s) % MOD};
}

pll operator-(const pll& l, const pll& r) {
    return {(l.f-r.f+MOD) % MOD,(l.s-r.s+MOD) % MOD};
}

pll operator*(const ll& l, const pll& r) {
    return {l*r.f % MOD,l*r.s % MOD};
}

ll powe(ll b, ll p) {
    return !p?1:powe(b*b%MOD,p/2)*(p&1?b:1)%MOD;
}

ll inv(ll x) {
    return powe(x,MOD-2);
}

string s; 

void gen() {
    po[0] = ipo[0] = {1,1};
    FOR(i,1,200000) {
        po[i] = po[i-1]*base;
        ipo[i] = {inv(po[i].f),inv(po[i].s)};
    }
    F0R(i,s.length()) cum[i+1] = cum[i]+int(s[i]-'a'+1)*po[i];
}

pll get(int l, int r) {
    return ipo[l]*(cum[r+1]-cum[l]);
}

int main() {
    cin >> s; // abacaba
    gen();
    F0R(i,s.length()) FOR(j,i,s.length()) cout << i << " " << j << " " << get(i,j).f << " " << get(i,j).s << "\n";
}

// read!
// ll vs. int!
