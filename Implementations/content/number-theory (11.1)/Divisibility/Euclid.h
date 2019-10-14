/**
 * Description: Euclidean Algorithm
 * Source: KACTL
 */

pl euclid(ll a, ll b) { // returns {x,y} such that a*x+b*y=gcd(a,b)
	if (!b) return {1,0};
	pl p = euclid(b,a%b);
	return {p.s,p.f-a/b*p.s};
}
ll invGeneral(ll a, ll b) { 
	pl p = euclid(a,b); assert(p.f*a+p.s*b == 1);
	return p.f+(p.f<0)*b;
}