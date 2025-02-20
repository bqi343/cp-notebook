/**
 * Description: Multiply two 64-bit integers mod another if 128-bit is not available.
	* modMul is equivalent to \texttt{(ul)(\_\_int128(a)*b\%mod)}. 
	* Works for $0\le a,b<mod<2^{63}.$
 * Source: KACTL
 * Verification: see "Faster Factoring"
 */

/// using db = long double;
using ul = uint64_t;
// ul modMul(ul a, ul b, const ul mod) {
// 	ll ret = a*b-mod*(ul)((db)a*b/mod);
// 	return ret+((ret<0)-(ret>=(ll)mod))*mod; }
ul modMul(ul a, ul b, const ul mod){
	return __int128(a) * __int128(b) % mod;
}
ul modPow(ul a, ul b, const ul mod) {
	if (b == 0) return 1;
	ul res = modPow(a,b/2,mod); res = modMul(res,res,mod);
	return b&1 ? modMul(res,a,mod) : res;
}
