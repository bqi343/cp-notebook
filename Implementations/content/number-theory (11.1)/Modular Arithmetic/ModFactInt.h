/**
 * Description: pre-compute factorial mod inverses,
 	* assumes $MOD$ is prime and $N < MOD$.
 * Time: O(N)
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/tle17c4p5
 */

#include "ModInt.h"

struct Factorials {
	vi invs, fac, ifac; // make sure to convert to LL before doing any multiplications ...
	void genFac(int N) {
		invs.rsz(N), fac.rsz(N), ifac.rsz(N); 
		invs[1] = fac[0] = ifac[0] = 1; 
		FOR(i,2,N) invs[i] = int(MOD-(ll)MOD/i*invs[MOD%i]%MOD);
		FOR(i,1,N) {
			fac[i] = int((ll)fac[i-1]*i%MOD);
			ifac[i] = int((ll)ifac[i-1]*invs[i]%MOD);
		}
	}
	int C(int a, int b) {
		if (a < b || b < 0) return 0;
		return (ll)fac[a]*ifac[b]%MOD*ifac[a-b]%MOD; 
	}
};
