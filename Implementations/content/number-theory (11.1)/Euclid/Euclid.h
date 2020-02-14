/**
 * Description: euclid finds $\{x,y\}$ such that $ax+by=\gcd(a,b)$ 
 	* and $|ax|,|by|\le \frac{ab}{\gcd(a,b)}.$ Should work for $a,b<2^{62}$
 * Source: KACTL
 * Time: O(\log ab)
 */

pl euclid(ll a, ll b) { 
	if (!b) return {1,0};
	pl p = euclid(b,a%b); return {p.s,p.f-a/b*p.s}; }
ll invGen(ll a, ll b) { 
	pl p = euclid(a,b); assert(p.f*a+p.s*b == 1); // gcd is 1
	return p.f+(p.f<0)*b; }