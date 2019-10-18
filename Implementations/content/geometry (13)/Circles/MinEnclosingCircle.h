/**
 * Description: computes minimum enclosing circle
 * Time: expected $O(N)$
 * Source: KACTL
 * Verification: USACO Camp 2019 Contest 2 #4
 */

#include "Circumcenter.h"

pair<P, T> mec(vP ps) {
	shuffle(all(ps), mt19937(time(0)));
	P o = ps[0]; T r = 0, EPS = 1 + 1e-8;
	F0R(i,sz(ps)) if (abs(o-ps[i]) > r*EPS) {
		o = ps[i], r = 0;
		F0R(j,i) if (abs(o-ps[j]) > r*EPS) {
			o = (ps[i]+ps[j])/2, r = abs(o-ps[i]);
			F0R(k,j) if (abs(o-ps[k]) > r*EPS) 
				tie(o,r) = ccCenter(ps[i],ps[j],ps[k]);
		}
	}
	return {o,r};
}