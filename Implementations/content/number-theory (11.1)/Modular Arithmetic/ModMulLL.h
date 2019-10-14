/**
 * Description: multiply two 64-bit integers mod another if 128-bit is not available
	* works for $0\le a,b<mod<2^{63}$
 * Source: KACTL
 * Verification: see "Faster Factoring"
 */

typedef unsigned long long ul;

// equivalent to (ul)(__int128(a)*b%mod)
ul modMul(ul a, ul b, const ul mod) {
	ll ret = a*b-mod*(ul)((ld)a*b/mod);
	return ret+((ret<0)-(ret>=(ll)mod))*mod;
}
ul modPow(ul a, ul b, const ul mod) {
	if (b == 0) return 1;
	ul res = modPow(a,b/2,mod);
	res = modMul(res,res,mod);
	if (b&1) return modMul(res,a,mod);
	return res;
}