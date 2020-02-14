/**
 * Description: Basic poly ops including division and interpolation.
 * Source: Own. Also see
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/PolyInterpolate.h
 	* https://github.com/ecnerwala/icpc-book/blob/master/content/numerical/fft.cpp
 * Verification: see FFT
 */

#include "../../number-theory (11.1)/Modular Arithmetic/ModInt.h"

typedef mi T; using poly = vector<T>;
void remz(poly& p) { while (sz(p) && p.bk==0) p.pop_back(); }
poly rev(poly p) { reverse(all(p)); return p; }
poly shift(poly p, int x) { p.insert(begin(p),x,0); return p; }
poly RSZ(poly p, int x) { p.rsz(x); return p; }
T eval(const poly& p, T x) {
	T res = 0; R0F(i,sz(p)) res = x*res+p[i]; 
	return res; }
poly dif(const poly& p) { // differentiate
	poly res; FOR(i,1,sz(p)) res.pb(i*p[i]); 
	return res; }
poly integ(const poly& p) { // integrate
	poly res(sz(p)+1); F0R(i,sz(p)) res[i+1] = p[i]/(i+1);
	return res; }

poly& operator+=(poly& l, const poly& r) {
	l.rsz(max(sz(l),sz(r))); F0R(i,sz(r)) l[i] += r[i]; 
	return l; }
poly& operator-=(poly& l, const poly& r) {
	l.rsz(max(sz(l),sz(r))); F0R(i,sz(r)) l[i] -= r[i]; 
	return l; }
poly& operator*=(poly& l, const T& r) { trav(t,l) t *= r; 
	return l;	 }
poly& operator/=(poly& l, const T& r) { trav(t,l) t /= r; 
	return l; }
poly operator+(poly l, const poly& r) { return l += r; }
poly operator-(poly l, const poly& r) { return l -= r; }
poly operator-(poly l) { trav(t,l) t *= -1; return l; }
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

pair<poly,poly> quoRem(poly a, poly b) { 
	assert(sz(b)); auto B = b.bk; assert(B != 0);
	B = 1/B; trav(t,b) t *= B;
	norm(a); poly q(max(sz(a)-sz(b)+1,0));
	while (sz(a) >= sz(b)) {
		q[sz(a)-sz(b)] = a.bk;
		F0R(i,sz(b)) a[i+sz(a)-sz(b)] -= a.bk*b[i];
		norm(a);
	}
	trav(t,q) t *= B; 
	return {q,a};
}
poly interpolate(vector<pair<T,T>> v) {
	poly ret, prod = {1}; trav(t,v) prod *= poly({-t.f,1});
	F0R(i,sz(v)) {
		T fac = 1; F0R(j,sz(v)) if (i != j) fac *= v[i].f-v[j].f;
		ret += v[i].s/fac*quoRem(prod,{-v[i].f,1}).f;
	}
	return ret;
}