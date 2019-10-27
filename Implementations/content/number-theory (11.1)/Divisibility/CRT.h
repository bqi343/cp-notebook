/**
 * Description: Chinese Remainder Theorem, combine $a.f\pmod{a.s}$ and $b.f\pmod{b.s}$ 
 	* into something $\pmod{\text{lcm}(a.s,b.s)},$
 	* should work for $ab<2^{62}$
 * Source: KACTL
 * Verification: Kattis generalchineseremainder
 */

#include "Euclid.h"

pl solve(pl a, pl b) {
	if (a.s < b.s) swap(a,b);
	ll x,y; tie(x,y) = euclid(a.s,b.s); 
	ll g = a.s*x+b.s*y, l = a.s/g*b.s;
	if ((b.f-a.f)%g) return {-1,-1}; // no solution
	// ?*a.s+a.f \equiv b.f \pmod{b.s}
	// ?=(b.f-a.f)/g*(a.s/g)^{-1} \pmod{b.s/g}
	x = (b.f-a.f)%b.s*x%b.s/g*a.s+a.f; 
	return {x+(x<0)*l,l};
}
