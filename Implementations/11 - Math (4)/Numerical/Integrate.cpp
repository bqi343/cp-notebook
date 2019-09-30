/**
 * Description: https://en.wikipedia.org/wiki/Simpson%27s_rule
 * Source: KACTL
 * Verification: ?
 */

// d f(d x) { return x*x+3*x+1; }

d quad(d (*f)(d), d a, d b) {
	const int n = 1000;
	d dif = (b-a)/2/n;
	d tot = f(a)+f(b);
	FOR(i,1,2*n) tot += f(a+i*dif)*(i&1?4:2);
	return tot*dif/3;
}