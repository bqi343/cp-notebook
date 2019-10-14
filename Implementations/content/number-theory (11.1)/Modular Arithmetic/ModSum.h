/**
 * Description: Sums of mod'ed arithmetic progressions
 * Source: KACTL
 * Verification: ?
 */

typedef unsigned long long ul;

ul sumsq(ul to) { return (to-1)*to/2; } // sum of 0..to-1

ul divsum(ul to, ul c, ul k, ul m) { // sum_{i=0}^{to-1}floor((ki+c)/m)
	ul res = k/m*sumsq(to)+c/m*to;
	k %= m; c %= m; if (!k) return res;
	ul to2 = (to*k+c)/m;
	return res+(to-1)*to2-divsum(to2,m-1-c,m,k); 
}

ll modsum(ul to, ll c, ll k, ll m) {
	c = (c%m+m)%m, k = (k%m+m)%m;
	return to*c+k*sumsq(to)-m*divsum(to,c,k,m);
}