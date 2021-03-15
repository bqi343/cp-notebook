/**
 * Description: Multipoint evaluation and interpolation
 * Time: O(N\log^2 N)
 */

#include "PolyInv.h"

void segProd(V<poly>& stor, poly& v, int ind, int l, int r) { // v -> places to evaluate at
	if (l == r) { stor[ind] = {-v[l],1}; return; }
	int m = (l+r)/2; segProd(stor,v,2*ind,l,m); segProd(stor,v,2*ind+1,m+1,r);
	stor[ind] = conv(stor[2*ind],stor[2*ind+1]);
}
void evalAll(V<poly>& stor, poly& res, poly v, int ind = 1) {
	v = divi(v,stor[ind]).s;
	if (sz(stor[ind]) == 2) { res.pb(sz(v)?v[0]:0); return; }
	evalAll(stor,res,v,2*ind); evalAll(stor,res,v,2*ind+1);
}
poly multiEval(poly v, poly p) {
	V<poly> stor(4*sz(p)); segProd(stor,p,1,0,sz(p)-1);
	poly res; evalAll(stor,res,v); return res; }

poly combAll(V<poly>& stor, poly& dems, int ind, int l, int r) {
	if (l == r) return {dems[l]};
	int m = (l+r)/2;
	poly a = combAll(stor,dems,2*ind,l,m), b = combAll(stor,dems,2*ind+1,m+1,r);
	return conv(a,stor[2*ind+1])+conv(b,stor[2*ind]);
}
poly interpolate(V<pair<T,T>> v) {
	int n = sz(v); poly x; each(t,v) x.pb(t.f);
	V<poly> stor(4*n); segProd(stor,x,1,0,n-1);
	poly dems; evalAll(stor,dems,dif(stor[1]));
	F0R(i,n) dems[i] = v[i].s/dems[i];
	return combAll(stor,dems,1,0,n-1);
}