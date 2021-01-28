/**
 * Description: $n$ points determine unique polynomial of degree $\le n-1$.
 	* For numerical precision pick $v[k].f = c*\cos(k/(n-1)*\pi), k=0 \dots n-1$.
 * Time: O(n^2)
 * Source: KACTL
 * Verification: see FFT
 */

 #include "Poly.h"

poly interpolate(vector<pair<T,T>> v) {
	int n = sz(v); poly res, tmp = {1};
	F0R(i,n) { T prod = 1; // modify poly for previous i points
		F0R(j,i) v[i].s -= prod*v[j].s, prod *= v[i].f-v[j].f;
		v[i].s /= prod; res += v[i].s*tmp; tmp *= poly{-v[i].f,1};
	} // add multiple of (x-v[0].f)*(x-v[1].f)*...*(x-v[i-1].f)
	return res;
}
/**
poly _interpolate(vector<pair<T,T>> v) {
	poly ret, prod = {1}; each(t,v) prod *= poly({-t.f,1});
	F0R(i,sz(v)) {
		T fac = 1; F0R(j,sz(v)) if (i != j) fac *= v[i].f-v[j].f;
		ret += v[i].s/fac*quoRem(prod,{-v[i].f,1}).f;
	}
	return ret;
}

vector<pair<T,T>> v; poly p = {4,6,7,11}, x = {1,3,9,16};
each(X,x) v.pb({X,eval(p,X)});
ps(interpolate(v));
*/
