/**
 * Description: Calculates smallest P such that x^P equiv 1 (mod p)
 * Source: Own
 * Verification: https://atcoder.jp/contests/jag2015summer-day4/tasks/icpc2015summer_day4_d
 */

#include "ModMulLL.h"
#include "../Primality/FactorBasic.h"

ll order(ll x, ll p) {
	if (__gcd(x,p) != 1) return 0;
	ll P = phi(p); auto a = factor(P);
	each(t,a) while (P % t.f == 0 
		&& modPow(x,P/t.f,p) == 1) P /= t.f;
	return P;
}
