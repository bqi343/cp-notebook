/**
 * Description: ?
 * Source: KACTL
	* https://en.wikipedia.org/wiki/Simpson%27s_rule
 * Verification: https://codeforces.com/gym/101793/problem/C
 */

// db f(db x) { return x*x+3*x+1; }

db quad(db (*f)(db), db a, db b) {
	const int n = 1000;
	db dif = (b-a)/2/n, tot = f(a)+f(b);
	FOR(i,1,2*n) tot += f(a+i*dif)*(i&1?4:2);
	return tot*dif/3;
}