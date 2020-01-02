/**
 * Description: Basic polynomial operations including division and interpolation.
 * Source: Own. Also see
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/PolyInterpolate.h
 	* https://github.com/ecnerwala/icpc-book/blob/master/content/numerical/fft.cpp
 * Verification: see FFT
 */

namespace VecOp {
	typedef ld T; using poly = vector<T>;
	poly rev(poly v) { reverse(all(v)); return v; }
	poly shift(poly v, int x) { v.ins(begin(v),x,0); return v; }
	poly& remLead(poly& v) { 
		while (sz(v) && v.bk == 0) v.pop_back(); return v; }
	T eval(const poly& v, T x) {
		T res = 0; R0F(i,sz(v)) res = x*res+v[i]; return res; }
	poly dif(const poly& v)	 {
		poly res; FOR(i,1,sz(v)) res.pb(i*v[i]); return res; }
	poly integ(const poly& v)  {
		poly res(sz(v)+1); F0R(i,sz(v)) res[i+1] = v[i]/(i+1);
		return res; }
	
	poly& operator+=(poly& l, const poly& r) {
		l.rsz(max(sz(l),sz(r))); F0R(i,sz(r)) l[i] += r[i]; 
		return l; }
	poly& operator-=(poly& l, const poly& r) {
		l.rsz(max(sz(l),sz(r))); F0R(i,sz(r)) l[i] -= r[i]; 
		return l; }
	poly& operator*=(poly& l, const T& r) { 
		trav(t,l) t *= r; return l;	 }
	poly& operator/=(poly& l, const T& r) { 
		trav(t,l) t /= r; return l; }

	poly operator+(poly l, const poly& r) { return l += r; }
	poly operator-(poly l, const poly& r) { return l -= r; }
	poly operator*(poly l, const T& r) { return l *= r; }
	poly operator*(const T& r, const poly& l) { return l*r; }
	poly operator/(poly l, const T& r) { return l /= r;	 }
	poly operator*(const poly& l, const poly& r) {
		if (!min(sz(l),sz(r))) return {};
		poly x(sz(l)+sz(r)-1); 
		F0R(i,sz(l)) F0R(j,sz(r)) x[i+j] += l[i]*r[j];
		return x;
	}
	poly& operator*=(poly& l, const poly& r) { return l = l*r; }
	
	pair<poly,poly> qr(poly a, poly b) { 
		assert(sz(b)); auto B = b.bk; assert(B != 0);
		B = 1/B; trav(t,b) t *= B;
		remLead(a); poly q(max(sz(a)-sz(b)+1,0));
		while (sz(a) >= sz(b)) {
			q[sz(a)-sz(b)] = a.bk;
			F0R(i,sz(b)) a[i+sz(a)-sz(b)] -= a.bk*b[i];
			remLead(a);
		}
		trav(t,q) t *= B; return {q,a};
	}
	poly quo(const poly& a, const poly& b) { return qr(a,b).f; }
	poly rem(const poly& a, const poly& b) { return qr(a,b).s; }
	poly interpolate(vector<pair<T,T>> v) {
		poly ret, prod = {1}; trav(t,v) prod *= poly({-t.f,1});
		F0R(i,sz(v)) {
			T fac = 1; F0R(j,sz(v)) if (i != j) fac *= v[i].f-v[j].f;
			ret += v[i].s/fac*quo(prod,{-v[i].f,1});
		}
		return ret;
	}
}
using namespace VecOp;