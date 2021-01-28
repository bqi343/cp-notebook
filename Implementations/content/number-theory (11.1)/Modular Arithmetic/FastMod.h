/**
 * Description: Barrett reduction computes $a \% b$ about 4 times faster than usual 
 	* where $b>1$ is constant but not known at compile time. Division by $b$ is replaced
 	* by multiplication by m and shifting right 64 bits.
 * Source: KACTL
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/various/FastMod.h
 	* https://en.wikipedia.org/wiki/Barrett_reduction
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=1045
 */

using ul = uint64_t; using L = __uint128_t;
struct FastMod {
	ul b,m; FastMod(ul _b) : b(_b), m(ul((L(1)<<64)/_b)) {}
	ul reduce(ul a) {
		ul q = (ul)((L(m)*a)>>64), r = a-q*b;
		return r>=b?r-b:r; }
};