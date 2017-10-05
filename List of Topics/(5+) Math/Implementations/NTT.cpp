// https://github.com/kth-competitive-programming/kactl/blob/master/content/number-theory/NTT.h

/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;

const ll mod = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

typedef vector<ll> vl;

ll modpow(ll b, ll p) { // MOD is prime
    ll ans = 1;
    while (p) {
        if (p&1) ans = ans*b % MOD;
        p >>= 1;
        b = b*b % MOD;
    }
    return ans;
}

void ntt(ll* x, ll* temp, ll* roots, int N, int skip) {
	if (N == 1) return;
	int n2 = N/2;
	ntt(x     , temp, roots, n2, skip*2);
	ntt(x+skip, temp, roots, n2, skip*2);
	F0R(i,N) temp[i] = x[i*skip];
    F0R(i,n2) {
		ll s = temp[2*i], t = temp[2*i+1] * roots[skip*i];
		x[skip*i] = (s + t) % mod; x[skip*(i+n2)] = (s - t) % mod;
	}
}

void ntt(vl& x, bool inv = false) {
	ll e = modpow(root, (mod-1) / int(x.size()));
	if (inv) e = modpow(e, mod-2);
	vl roots(x.size(), 1), temp = roots;
	FOR(i,1,x.size()) roots[i] = roots[i-1] * e % mod;
	ntt(&x[0], &temp[0], &roots[0], x.size(), 1);
}

vl conv(vl a, vl b) {
	int s = int(a.size()) + int(b.size()) - 1; if (s <= 0) return {};
	int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
	if (s <= 200) { // (factor 10 optimization for |a|,|b| = 10)
		vl c(s);
		F0R(i,a.size()) F0R(j,b.size())
			c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
		return c;
	}
	a.resize(n); ntt(a);
	b.resize(n); ntt(b);
	vl c(n); ll d = modpow(n, mod-2);
	F0R(i,n) c[i] = a[i] * b[i] % mod * d % mod;
	ntt(c, true); c.resize(s); return c;
}

int main() {
    
}