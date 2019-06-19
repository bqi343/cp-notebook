/**
 * Description: multiply two polynomials
    * [Wikipedia](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
 * Source: kevinsogo (https://www.hackerrank.com/contests/noi-ph-2019/challenges/yet-another-packing-problem/editorial)
    * also see http://codeforces.com/contest/623/submission/15807539
 * Verification: 
    * https://open.kattis.com/problems/polymul2
 */

int size(int s) { return s > 1 ? 32-__builtin_clz(s-1) : 0; }

void karatsuba(ll *a, ll *b, ll *c, ll *t, int n) {
    int ca = 0, cb = 0; F0R(i,n) ca += !!a[i], cb += !!b[i];
    if (min(ca, cb) <= 1500 / n) { // few numbers to multiply
        if (ca > cb) swap(a, b);
        F0R(i,n) if (a[i]) F0R(j,n) c[i+j] += a[i]*b[j];
    } else {
        int h = n >> 1;
        karatsuba(a, b, c, t, h);
        karatsuba(a+h, b+h, c+n, t, h);
        F0R(i,h) a[i] += a[i+h], b[i] += b[i+h];
        karatsuba(a, b, t, t+n, h);
        F0R(i,h) a[i] -= a[i+h], b[i] -= b[i+h];
        F0R(i,n) t[i] -= c[i]+c[i+n];
        F0R(i,n) c[i+h] += t[i], t[i] = 0;
    }
}

vl conv(vl a, vl b) {
    int sa = sz(a), sb = sz(b); if (!sa || !sb) return {};
    int l = 1<<size(max(sz(a),sz(b))); a.resz(l), b.resz(l);
    vl c(2*l), t(2*l); F0R(i,2*l) t[i] = 0; karatsuba(&a[0], &b[0], &c[0], &t[0], l);
    c.resz(sa+sb-1);
    return c;
}
