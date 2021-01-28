/**
 * Description: pre-compute factorial mod inverses,
 	* assumes $MOD$ is prime and $SZ < MOD$.
 * Time: O(SZ)
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/tle17c4p5
 */

vi invs, fac, ifac; // make sure to convert to LL before doing any multiplications ...
void genFac(int SZ) {
	invs.rsz(SZ), fac.rsz(SZ), ifac.rsz(SZ); 
	invs[1] = fac[0] = ifac[0] = 1; 
	FOR(i,2,SZ) invs[i] = int(MOD-(ll)MOD/i*invs[MOD%i]%MOD);
	FOR(i,1,SZ) {
		fac[i] = int((ll)fac[i-1]*i%MOD);
		ifac[i] = int((ll)ifac[i-1]*invs[i]%MOD);
	}
}
/**
ll comb(int a, int b) {
	if (a < b || b < 0) return 0;
	return (ll)fac[a]*ifac[b]%MOD*ifac[a-b]%MOD;
}
*/