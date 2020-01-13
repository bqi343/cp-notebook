 /**
 * Description: internal and external tangents between two circles
 * Source: Own
 * Verification: USACO Laser Cows
 */

#include "Circle.h"

P tangent(P x, circ y, int t = 0) {
	y.s = abs(y.s); // abs needed because internal calls y.s < 0
	if (y.s == 0) return y.f;
	T d = abs(x-y.f);
	P a = pow(y.s/d,2)*(x-y.f)+y.f;
	P b = sqrt(d*d-y.s*y.s)/d*y.s*unit(x-y.f)*dir(PI/2); 
	return t == 0 ? a+b : a-b;
}
vector<pair<P,P>> external(circ x, circ y) { 
	vector<pair<P,P>> v; 
	if (x.s == y.s) {
		P tmp = unit(x.f-y.f)*x.s*dir(PI/2);
		v.pb(mp(x.f+tmp,y.f+tmp));
		v.pb(mp(x.f-tmp,y.f-tmp));
	} else {
		P p = (y.s*x.f-x.s*y.f)/(y.s-x.s);
		F0R(i,2) v.pb({tangent(p,x,i),tangent(p,y,i)});
	}
	return v;
}
vector<pair<P,P>> internal(circ x, circ y) { 
	x.s *= -1; return external(x,y); }
