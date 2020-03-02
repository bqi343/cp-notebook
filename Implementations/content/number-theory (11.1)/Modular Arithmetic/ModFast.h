/**
 * Description: Unused. Barrett reduction computes $a \% b$ about 4 times faster than usual, 
 	* where $b$ is constant but not known at compile time. Fails for $b = 1$.
 * Source: KACTL
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/various/FastMod.h
 	* https://en.wikipedia.org/wiki/Barrett_reduction
 * Verification: ?
 */

typedef unsigned long long ul; typedef __uint128_t L;
struct ModFast {
	ul b,m; ModFast(ul b) : b(b), m(ul((L(1)<<64)/b)) {}
	ul reduce(ul a) {
		ul q = (ul)((L(m)*a)>>64), r = a-q*b;
		return r>=b?r-b:r; }
};