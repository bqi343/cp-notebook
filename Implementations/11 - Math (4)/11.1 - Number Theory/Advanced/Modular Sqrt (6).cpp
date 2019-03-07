/**
 * Description: find sqrt of integer via a prime
 * Source: http://www.math.vt.edu/people/brown/class_homepages/shanks_tonelli.pdf
 * Verification: https://www.spoj.com/problems/CRYPTO1
 */

ll modsqrt(mi a) { // change modular int to accept long longs
    mi p = exp(a,(MOD-1)/2); if (p != 1) return p == 0 ? 0 : -1;
    ll s = MOD-1, e = 0; while (s % 2 == 0) s /= 2, e ++;
    mi n = 1; while (exp(n,(MOD-1)/2) == 1) n = (ll)(n)+1; // find non-square residue

    mi x = exp(a,(s+1)/2), b = exp(a,s), g = exp(n,s);
    int r = e;
    while (1) {
        mi B = b; int m = 0; while (B != 1) B *= B, m ++;
        if (m == 0) break;
        F0R(i,r-m-1) g *= g;
        x *= g; g *= g; b *= g; r = m;

        /* Explanation:
         * Initially, x^2=ab, ord(b) = 2^m, ord(g) = 2^r where m<r
         * g = g^{2^{r-m-1}} -> ord(g) = 2^{m+1}
         * if x'=x*g, then b' = b*g^2
                (b')^{2^{m-1}} = (b*g^2)^{2^{m-1}}
                               = b^{2^{m-1}}*g^{2^m}
                               = -1*-1
                               = 1
            -> ord(b')|ord(b)/2
         * m decreases by at least one each iteration
         */
    }
    return min((ll)x,MOD-(ll)x);
}
