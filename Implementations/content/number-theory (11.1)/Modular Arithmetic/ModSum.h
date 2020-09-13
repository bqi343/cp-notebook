/**
 * Description: divsum computes $\sum_{i=0}^{to-1}\left\lfloor\frac{ki+c}{m}\right\rfloor,$ 
 	* modsum defined similarly
 * Time: O(\log m)
 * Source: KACTL
 	* https://codeforces.com/gym/102135/problem/G
 * Verification: https://open.kattis.com/problems/aladin
 */

using ul = unsigned long long;
ul sumsq(ul to) { return (to-1)*to/2; } // sum of 0..to-1
ul divsum(ul to, ul c, ul k, ul m) { // k >= 0, m > 0
	ul res = k/m*sumsq(to)+c/m*to;
	k %= m; c %= m; if (!k) return res;
	ul to2 = (to*k+c)/m;
	return res+(to-1)*to2-divsum(to2,m-1-c,m,k); 
}
ll modsum(ul to, ll c, ll k, ll m) {
	c = (c%m+m)%m, k = (k%m+m)%m;
	return to*c+k*sumsq(to)-m*divsum(to,c,k,m); }
