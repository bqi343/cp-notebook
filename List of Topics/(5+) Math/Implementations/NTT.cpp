// https://github.com/kth-competitive-programming/kactl/blob/master/content/number-theory/NTT.h 
// also see FFT

const ll mod = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

typedef vector<ll> vl;

ll modpow(ll b, ll p) { // mod is prime
    return !p?1:modpow(b*b%mod,p/2)*(p&1?b:1)%mod;
}

ll inv (ll b) {
    return modpow(b,mod-2);
}

int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}

vl ntt (vl &as) {
    int n = as.size(), k = get(n);
    
    vi rev(n);
    rev[0] = 0;
    int high1 = -1;
    FOR(i,1,n) {
        if ((i & (i - 1)) == 0) high1++;
        rev[i] = rev[i ^ (1 << high1)]; 
        rev[i] |= (1 << (k - high1 - 1)); 
    }
    
    vl roots(n);
    roots[0] = 1;
    roots[1] = modpow(root,(mod-1)/n);
    FOR(i,2,n) roots[i] = roots[1]*roots[i-1]%mod;
    
    vl cur(n);
    F0R(i,n) cur[i] = as[rev[i]];
    
    for (int len = 1; len < n; len <<= 1) {
        vl ncur(n);
        int rstep = roots.size() / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            F0R(i,len) {
                ll val = roots[i*rstep]*cur[p1 + len] % mod;
                ncur[pdest] = (cur[p1] + val) % mod;
                ncur[pdest + len] = ((cur[p1]-val)%mod+mod)%mod;
                pdest++, p1++;
            }
            pdest += len;
        }
        cur.swap(ncur);
    }
    return cur;
}
 
vl ntt_rev(vl &as) {
    vl res = ntt(as);
    
    ll n1 = inv(as.size());
    F0R(i,sz(res)) res[i] = res[i]*n1%mod;
    reverse(res.begin() + 1, res.end());
    return res;
}

vl conv(vl a, vl b) {
	int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
	if (s <= 0) return {};
	
	a.resize(n); a = ntt(a);
	b.resize(n); b = ntt(b);
	
	F0R(i,n) a[i] = a[i]*b[i]%mod;
	a = ntt_rev(a);
	
	a.resize(s);
	return a;
}