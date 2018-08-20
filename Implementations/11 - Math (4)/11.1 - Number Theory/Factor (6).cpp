/**
* Source: KACTL
* Description: Factors integers up to 2^{60}
* Usage: https://www.spoj.com/problems/FACT0/
*/

using namespace RPM;

vl pr;

template<int SZ> struct Sieve { // https://open.kattis.com/problems/primesieve
    bitset<SZ+1> comp;
    Sieve() {
        for (int i = 2; i*i <= SZ; ++i) if (!comp[i]) 
            for (int j = i*i; j <= SZ; j += i) comp[j] = 1;
        FOR(i,2,SZ+1) if (!comp[i]) pr.pb(i);
    }
    bool isPrime(int x) {
        if (x == 1) return 0;
        return !comp[x];
    }
};

Sieve<1<<20> S; // should take care of all primes up to n^(1/3)

bool prime(ll p) { // miller-rabin
	if (p == 2) return true;
	if (p == 1 || p % 2 == 0) return false;
	ll s = p - 1;
	while (s % 2 == 0) s /= 2;
	F0R(i,15) {
		ll a = rand() % (p - 1) + 1, tmp = s;
		ll mod = mod_pow(a, tmp, p);
		while (tmp != p - 1 && mod != 1 && mod != p - 1) {
			mod = mod_mul(mod, mod, p);
			tmp *= 2;
		}
		if (mod != p - 1 && tmp % 2 == 0) return false;
	}
	return true;
}

ll f(ll a, ll n, ll &has) { return (mod_mul(a, a, n) + has) % n; }

vpl factor(ll d) {
	vpl res;
	
	for (int i = 0; i < sz(pr) && pr[i]*pr[i] <= d; i++) if (d % pr[i] == 0) {
	    int co = 0;
		while (d % pr[i] == 0) d /= pr[i], co ++;
		res.pb({pr[i],co});
    }
		
	if (d > 1) { // d is now a product of at most 2 primes.
		if (prime(d)) res.pb({d,1});
		else while (1) {
			ll has = rand() % 2321 + 47;
			ll x = 2, y = 2, c = 1;
			for (; c == 1; c = __gcd((y > x ? y - x : x - y), d)) {
				x = f(x, d, has);
				y = f(f(y, d, has), d, has);
			}
			if (c != d) {
			    d /= c; if (d > c) swap(d,c);
			    if (c == d) res.pb({c,2});
			    else res.pb({c,1}), res.pb({d,1});
				break;
			}
		}
	}
	
	return res;
}
