/**
 * Description: Finds the argument minimizing the function $f$ in the interval $[a,b]$ assuming 
 	* $f$ is unimodal on the interval, i.e. has only one local minimum. The maximum error in the 
 	* result is $eps$. Works equally well for maximization with a small change in the code. 
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/GoldenSectionSearch.h
 * Verification: https://codeforces.com/contest/1427/problem/H
 * Usage: gss(-1000,1000,[](db x) { return 4+x+.3*x*x; }); // -5/3
 * Time: O(\log((b-a) / \epsilon))
 */

/// It is important for r to be precise, otherwise we don't necessarily maintain the inequality a < x1 < x2 < b.
db gss(db a, db b, function<db(db)> f) {
	db r = (sqrt(5)-1)/2, eps = 1e-7;
	db x1 = b - r*(b-a), x2 = a + r*(b-a);
	db f1 = f(x1), f2 = f(x2);
	while (b-a > eps)
		if (f1 < f2) { // change to > to find maximum
			b = x2; x2 = x1; f2 = f1;
			x1 = b - r*(b-a); f1 = f(x1);
		} else {
			a = x1; x1 = x2; f1 = f2;
			x2 = a + r*(b-a); f2 = f(x2);
		}
	return a;
}