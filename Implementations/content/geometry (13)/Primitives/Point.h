/**
 * Description: Easy Geo
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 * Verification: various
 */

typedef ld T;
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }

namespace Point {
	typedef pair<T,T> P;
	typedef vector<P> vP;

	P dir(T ang) {
		auto c = exp(ang*complex<T>(0,1));
		return P(c.real(),c.imag());
	}
	
	T norm(P x) { return x.f*x.f+x.s*x.s; }
	T abs(P x) { return sqrt(norm(x)); }
	T angle(P x) { return atan2(x.s,x.f); }
	P conj(P x) { return P(x.f,-x.s); }
	
	P operator+(const P& l, const P& r) { return P(l.f+r.f,l.s+r.s); }
	P operator-(const P& l, const P& r) { return P(l.f-r.f,l.s-r.s); }
	P operator*(const P& l, const T& r) { return P(l.f*r,l.s*r); }
	P operator*(const T& l, const P& r) { return r*l; }
	P operator/(const P& l, const T& r) { return P(l.f/r,l.s/r); }
	P operator*(const P& l, const P& r) { return P(l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s); }
	P operator/(const P& l, const P& r) { return l*conj(r)/norm(r); }
	
	P& operator+=(P& l, const P& r) { return l = l+r; }
	P& operator-=(P& l, const P& r) { return l = l-r; }
	P& operator*=(P& l, const T& r) { return l = l*r; }
	P& operator/=(P& l, const T& r) { return l = l/r; }
	P& operator*=(P& l, const P& r) { return l = l*r; }
	P& operator/=(P& l, const P& r) { return l = l/r; }
	
	P unit(P x) { return x/abs(x); }
	T dot(P a, P b) { return (conj(a)*b).f; }
	T cross(P a, P b) { return (conj(a)*b).s; }
	T cross(P p, P a, P b) { return cross(a-p,b-p); }
	P rotate(P a, T b) { return a*P(cos(b),sin(b)); }

	P reflect(P p, P a, P b) { return a+conj((p-a)/(b-a))*(b-a); }
	P foot(P p, P a, P b) { return (p+reflect(p,a,b))/(T)2; }
	bool onSeg(P p, P a, P b) { return cross(a,b,p) == 0 && dot(p-a,p-b) <= 0; }
};

using namespace Point;