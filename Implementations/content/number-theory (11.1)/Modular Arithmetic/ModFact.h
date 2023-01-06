/**
 * Description: Combinations modulo a prime $MOD$. Assumes $2\le N \le MOD$.
 * Time: O(N)
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/tle17c4p5
 * Usage: F.init(10); F.C(6, 4); // 15
 */

#include "ModInt.h"

struct {
	vmi invs, fac, ifac;
	void init(int N) { // idempotent
		invs.rsz(N), fac.rsz(N), ifac.rsz(N); 
		invs[1] = fac[0] = ifac[0] = 1; 
		FOR(i,2,N) invs[i] = mi(-(ll)MOD/i*(int)invs[MOD%i]);
		FOR(i,1,N) fac[i] = fac[i-1]*i, ifac[i] = ifac[i-1]*invs[i];
	}
	mi C(int a, int b) {
		if (a < b || b < 0) return 0;
		return fac[a]*ifac[b]*ifac[a-b]; 
	}
} F;