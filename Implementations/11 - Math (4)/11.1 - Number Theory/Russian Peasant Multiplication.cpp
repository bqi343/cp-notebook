/**
* Description: Russian Peasant Multiplication
    * multiply two 64-bit integers mod another if 128-bit is not available
* Source: KACTL
* Verification: ?
*/

typedef unsigned long long ul;

namespace rpm {
    const int bits = 14; // if all numbers are less than 2^k, set bits = 64-k
    const ul po = (ul)1<<bits;
    
    ul mod_mul(ul a, ul b, ul &c) {  // return (__int128(a)*b) % c;
    	ul x = 0;
    	for (; b; b >>= bits, a = (a << bits) % c) 
    		x = (x + (a * (b & (po - 1))) % c) % c;
    	return x;
    }
    
    ul mod_pow(ul a, ul b, ul mod) {
    	if (b == 0) return 1;
    	ul res = mod_pow(a, b / 2, mod);
    	res = mod_mul(res, res, mod);
    	if (b & 1) return mod_mul(res, a, mod);
    	return res;
    }
}

using namespace rpm;