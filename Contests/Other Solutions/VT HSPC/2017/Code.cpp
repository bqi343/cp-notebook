#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
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

typedef complex<double> cd;
typedef vector<cd> vcd;
typedef vector<ll> vl;

int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}
    
namespace Poly {
    namespace NTT {
        const ll mod = (119 << 23) + 1, root = 3; // = 998244353
        // For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
        // (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.
            
        ll modpow(ll b, ll p) { return !p?1:modpow(b*b%mod,p/2)*(p&1?b:1)%mod; }
        
        ll inv (ll b) { return modpow(b,mod-2); }
        
        vl ntt(vl& a) { 
            int n = a.size(), x = get(n); 
            vl res, RES(n), roots(n);
            roots[0] = 1, roots[1] = modpow(root,(mod-1)/n);
            FOR(i,2,n) roots[i] = roots[i-1]*roots[1] % mod;
            
            res = a;
            FOR(i,1,x+1) {
                int inc = n>>i;
                F0R(j,inc) for (int k = 0; k < n; k += inc)  // 1<<i numbers
                    RES[k+j] = (res[2*k%n+j]+roots[k]*res[2*k%n+j+inc]) % mod;
                swap(res,RES);
            }
            
            return res;
        }
        
        vl ntt_rev(vl& a) {
            vl res = ntt(a);
            ll in = inv(a.size());
            F0R(i,sz(res)) res[i] = res[i]*in % mod;
            reverse(res.begin() + 1, res.end());
            return res;
        }
        
        vl conv(vl a, vl b) {
            int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
            if (s <= 0) return {};
            
            if (s <= 200) {
                vl c(s);
                F0R(i,sz(a)) F0R(j,sz(b))
                    c[i + j] = (c[i + j] + a[i] * b[j])%mod;
                return c;
            }
            
            a.resize(n); a = ntt(a);
            b.resize(n); b = ntt(b);
            
            F0R(i,n) a[i] = a[i]*b[i] % mod;
            a = ntt_rev(a);
            
            a.resize(s);
            return a;
        }
    }
}

struct Base {
    vl po10[21];
    const int base = 27;
    
    Base() {
        po10[0] = {10};
        FOR(i,1,21) {
            po10[i] = Poly::NTT::conv(po10[i-1],po10[i-1]);
            normalize(po10[i]);
        }
    }
    
    void normalize(vl& x) {
        F0R(i,sz(x)) if (x[i] >= base) {
            if (i == sz(x)-1) x.pb(0);
            x[i+1] += x[i]/base;
            x[i] %= base;
        }
        while (sz(x) && !x.back()) x.pop_back();
    }
    
    vl bruteforce(vl in) {
        ll t = 0, po = 1;
        F0R(i,sz(in)) { t += in[i]*po; po *= 10; }
        vl ret;
        while (t) { ret.pb(t%27); t /= 27; }
        return ret;
    }
    
    vl convert(vl in) {
        if (sz(in) <= 9) return bruteforce(in);
        vl l = convert(vl(in.begin(),in.begin()+sz(in)/2));
        vl r = convert(vl(in.begin()+sz(in)/2,in.end()));
        
        r = Poly::NTT::conv(r,po10[get(sz(in))-1]);
        normalize(r);
        
        int z = max(sz(l),sz(r));
        r.resize(z);
        F0R(i,sz(l)) r[i] += l[i];
        normalize(r);
        return r;
    }
};

Base B;

const int MOD = 1<<20;

int n,x,sum[250000];
vi t;
string c,s;
vl C,D;

int getnex(int x) {
    return (33*x+1)%MOD;
}

void gen() {
    cin >> n >> x; 
    getline(cin,s); getline(cin,s);
    t.pb(0);
    while (t.size()<MOD){
        int x = getnex(t.back());
        t.pb(x); 
    }
    int cur = 1;
    F0R(i,x) {
        sum[0] = (sum[0]+t[cur])%MOD;
        cur = (cur+x)%MOD;
    }
    c = to_string(sum[0]);
    FOR(i,1,x) {
        sum[i] = (33*sum[i-1]+x) % MOD;
        c += to_string(sum[i]);
    }
}

void con() { // convert to base 27 ...
    F0Rd(i,sz(c)) C.pb(c[i]-'0');
    while (__builtin_popcount(sz(C)) > 1) C.pb(0);
    D = B.convert(C);
    reverse(all(D));
}

int getval(char c){
    if (c == ' ') return 26;
    return c-'A';
}

char rev(int x) {
    if (x == 26) return ' ';
    return char(x+'A');
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    gen();
    con();
    F0R(i,sz(s)) {
        int t = (getval(s[i])+D[i])%27;
        cout << rev(t);
    }
}

// read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!read!
// ll vs. int!