/**
 * Description: Unused. Fast integration using adaptive Simpson's rule.
 * Source: KACTL
	* https://en.wikipedia.org/wiki/Adaptive_Simpson%27s_method
 * Verification: ?
 * Usage: 
	db z, y;
	db h(db x) { return x*x + y*y + z*z <= 1; }
	db g(db y) { ::y = y; return quad(h, -1, 1); }
	db f(db z) { ::z = z; return quad(g, -1, 1); }
	db sphereVol = quad(f,-1,1), pi = sphereVol*3/4;
 */

/// db f(db x) { return x*x+3*x+1; }
db simpson(db (*f)(db), db a, db b) {
	db c = (a+b)/2; return (f(a)+4*f(c)+f(b))*(b-a)/6; }
db rec(db (*f)(db), db a, db b, db eps, db S) {
	db c = (a+b)/2;
	db S1 = simpson(f,a,c), S2 = simpson(f,c,b), T = S1+S2;
	if (abs(T-S)<=15*eps || b-a<1e-10) return T+(T-S)/15;
	return rec(f,a,c,eps/2,S1)+rec(f,c,b,eps/2,S2);
}
db quad(db (*f)(db), db a, db b, db eps = 1e-8) {
	return rec(f,a,b,eps,simpson(f,a,b)); }