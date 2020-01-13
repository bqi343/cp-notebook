/**
 * Description: Given fractions $a<b$ with non-negative numerators and denominators, 
 	* finds fraction $f$ with lowest denominator such that $a<f<b.$ Should work with 
	* all numbers less than $2^{62}.$
 * Source: ?
 * Verification: http://acm.hdu.edu.cn/showproblem.php?pid=6624
 */

pl bet(pl a, pl b) {
	ll num = a.f/a.s; a.f -= num*a.s, b.f -= num*b.s;
	if (b.f > b.s) return {1+num,1};
	auto x = bet({b.s,b.f},{a.s,a.f});
	return {x.s+num*x.f,x.f};
}
