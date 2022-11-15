/**
 * Description: Counts $\#$ of lattice points $(x,y)$ in the triangle 
 * $1 \le x, 1 \le y, ax+by \le s$ $\pmod{2^{64}}$ and related quantities.
 * Time: O(\log ab)
 * Source: KACTL
   * https://github.com/ecnerwala/cp-book/blob/master/src/lattice_cnt.hpp
 * Verification: https://open.kattis.com/problems/aladin
   * https://codeforces.com/gym/102135/problem/G
 */

using ul = uint64_t;
ul sum2(ul n) { return n/2*((n-1)|1); } // sum(0..n-1)
// \return |{(x,y) | 1 <= x, 1 <= y, a*x+b*y <= S}|
//       = sum_{i=1}^{qs} (S-a*i)/b
ul triSum(ul a, ul b, ul s) { assert(a > 0 && b > 0); /// s = a*qs+rs
	ul qs = s/a, rs = s%a; // ans = sum_{i=0}^{qs-1}(i*a+rs)/b
	ul ad = a/b*sum2(qs)+rs/b*qs; a %= b, rs %= b;
	return ad+(a?triSum(b,a,a*qs+rs):0); // reduce if a >= b
} // then swap x and y axes and recurse

// \return sum_{x=0}^{n-1} (a*x+b)/m
//       = |{(x,y) | 0 < m*y <= a*x+b < a*n+b}|
// assuming a*n+b does not overflow
ul divSum(ul n, ul a, ul b, ul m) { assert(m > 0);
	ul extra = b/m*n; b %= m;
	return extra+(a?triSum(m,a,a*n+b):0); }
// \return sum_{x=0}^{n-1} (a*x+b)%m
ul modSum(ul n, ll a, ll b, ul m) { assert(m > 0);
	a = (a%m+m)%m, b = (b%m+m)%m;
	return a*sum2(n)+b*n-m*divSum(n,a,b,m); }