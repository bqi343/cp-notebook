/**
 * Description: multiply two polynomials
 * Time: $O(N^{\log_2 3})$
 * Source: kevinsogo 
	* https://www.hackerrank.com/contests/noi-ph-2019/challenges/yet-another-packing-problem/editorial
	* also see http://codeforces.com/contest/623/submission/15807539
	* https://en.wikipedia.org/wiki/Karatsuba\_algorithm
 * Verification: https://open.kattis.com/problems/polymul2
 */

int size(int s) { return s > 1 ? 32-__builtin_clz(s-1) : 0; }

void karatsuba(ll *a, ll *b, ll *c, ll *t, int n) {
	int ca = 0, cb = 0; F0R(i,n) ca += !!a[i], cb += !!b[i];
	if (min(ca, cb) <= 1500/n) { // few numbers to multiply
		if (ca > cb) swap(a, b);
		F0R(i,n) if (a[i]) F0R(j,n) c[i+j] += a[i]*b[j];
	} else {
		int h = n >> 1;
		karatsuba(a, b, c, t, h); // a0*b0
		karatsuba(a+h, b+h, c+n, t, h); // a1*b1
		F0R(i,h) a[i] += a[i+h], b[i] += b[i+h]; 
		karatsuba(a, b, t, t+n, h); // (a0+a1)*(b0+b1)
		F0R(i,h) a[i] -= a[i+h], b[i] -= b[i+h];
		F0R(i,n) t[i] -= c[i]+c[i+n];
		F0R(i,n) c[i+h] += t[i], t[i] = 0;
	}
}

vl conv(vl a, vl b) {
	int sa = sz(a), sb = sz(b); if (!sa || !sb) return {};
	int n = 1<<size(max(sa,sb)); a.rsz(n), b.rsz(n);
	vl c(2*n), t(2*n); F0R(i,2*n) t[i] = 0; 
	karatsuba(&a[0], &b[0], &c[0], &t[0], n);
	c.rsz(sa+sb-1); return c;
}