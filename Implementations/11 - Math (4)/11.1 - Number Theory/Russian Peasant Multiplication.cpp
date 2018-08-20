/**
* Description: multiply two 64-bit integers mod another if 128-bit is not available
* Source: KACTL
*/

namespace RPM {
    const int bits = 15; // if all numbers are less than 2^k, set bits = 63-k
    const ll po = 1<<bits;
    
    ll mod_mul(ll a, ll b, ll &c) {  // return (__int128(a)*b) % c;
    	ll x = 0;
    	for (; b; b >>= bits, a = (a << bits) % c) 
    		x = (x + (a * (b & (po-1))) % c) % c;
    	return x;
    }
    
    ll mod_pow(ll a, ll b, ll mod) {
    	if (b == 0) return 1;
    	ll res = mod_pow(a, b / 2, mod);
    	res = mod_mul(res, res, mod);
    	if (b & 1) return mod_mul(res, a, mod);
    	return res;
    }
}