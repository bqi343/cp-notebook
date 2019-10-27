/**
 * Description: Integration of a function over an interval using
   * Simpson's rule. The error should be proportional to $dif^4$, although in
   * practice you will want to verify that the result is stable to desired
   * precision when epsilon changes.
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