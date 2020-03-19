bool prime(ll p) { // Miller-Rabin
	if (p == 2) return 1;
	if (p == 1 || p % 2 == 0) return 0;
	ll s = p-1; while (s%2 == 0) s /= 2;
	F0R(i,15) { // strong liar with probability <= 1/4
		ll a = rand()%(p-1)+1, tmp = s;
		ll mod = modPow(a,tmp,p);
		while (tmp != p-1 && mod != 1 && mod != p-1)
			mod = modMul(mod,mod,p), tmp *= 2;
		if (mod != p-1 && tmp%2 == 0) return 0;
	}
	return 1;
}

bool prime(ll p) { // Miller-Rabin
	if (p == 2) return 1;
	if (p == 1 || p % 2 == 0) return 0;
	ll s = p-1; while (s%2 == 0) s /= 2;
	F0R(i,15) { // strong liar with probability <= 1/4
		ll a = rand()%(p-1)+1, tmp = s;
		ll mod = modPow(a,tmp,p);
		while (tmp != p-1 && mod != 1 && mod != p-1)
			mod = modMul(mod,mod,p), tmp *= 2;
		if (mod != p-1 && tmp%2 == 0) return 0;
	}
	return 1;
}

ll f(ll a, ll n, ll has) { return (modMul(a,a,n)+has)%n; }
ll pollard(ll n) {
	while (1) {
		ll has = rand()%2321+47;
		ll x = 2, y = 2, c = 1;
		for (; c == 1; c = __gcd(abs(x-y), d)) {
			x = f(x, d, has);
			y = f(f(y, d, has), d, has);
		} // should cycle in ~sqrt(smallest nontrivial divisor) 
		if (c != d) {
			break;
		}
	}
}