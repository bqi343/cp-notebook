/**
 * Description: find sqrt of integer via a prime
 * Source: http://www.math.vt.edu/people/brown/class_homepages/shanks_tonelli.pdf
 * Verification: https://www.spoj.com/problems/CRYPTO1
 */
 
int modsqrt(int a) {
    int p = po(a,(MOD-1)/2); if (p != 1) return p == 0 ? 0 : -1;
    int s = MOD-1, e = 0; while (s % 2 == 0) s /= 2, e ++;
    int n = 1; while (po(n,(MOD-1)/2) == 1) n ++; // find non-square residue 
    
    int x = po(a,(s+1)/2), b = po(a,s), g = po(n,s), r = e; 
    while (1) {
        int B = b, m = 0; while (B != 1) B = mul(B,B), m ++;
        if (m == 0) break;
        F0R(i,r-m-1) MUL(g,g); 
        MUL(x,g); MUL(g,g); MUL(b,g); r = m;

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
    ckmin(x,MOD-x); return x;
}