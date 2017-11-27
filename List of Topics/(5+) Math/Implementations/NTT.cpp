// inspired by
// https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FFT.h
// https://pastebin.com/3Tnj5mRu

const ll mod = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

typedef vector<ll> vl;

ll modpow(ll b, ll p) { return !p?1:modpow(b*b%mod,p/2)*(p&1?b:1)%mod; }

ll inv (ll b) { return modpow(b,mod-2); }

int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}

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
    
    a.resize(n); a = ntt(a);
    b.resize(n); b = ntt(b);
    
    F0R(i,n) a[i] = a[i]*b[i] % mod;
    a = ntt_rev(a);
    
    a.resize(s);
    return a;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    vl x = conv({1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8});
    for (auto a: x) cout << a << "\n";
}