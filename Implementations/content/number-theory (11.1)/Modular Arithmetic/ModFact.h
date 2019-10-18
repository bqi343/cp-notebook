/**
 * Description: pre-compute factorial mod inverses for $MOD$, 
 	* assumes $MOD$ is prime and $SZ < MOD$
 * Time: O(SZ)
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/tle17c4p5
 */

vl inv, fac, ifac;
void genInv(int SZ) {
	inv.rsz(SZ), fac.rsz(SZ), ifac.rsz(SZ);
	inv[1] = 1; FOR(i,2,SZ) inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
	fac[0] = ifac[0] = 1;
	FOR(i,1,SZ) {
		fac[i] = fac[i-1]*i%MOD;
		ifac[i] = ifac[i-1]*inv[i]%MOD;
	}
}