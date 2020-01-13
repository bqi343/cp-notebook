/**
 * Description: use in place of \texttt{complex<T>}
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 * Verification: various
 */

typedef ld T;
int sgn(T x) { return (x>0)-(x<0); }
T sq(T x) { return x*x; }

namespace Point {
	typedef pair<T,T> P;
	typedef vector<P> vP;
	T norm(const P& x) { return sq(x.f)+sq(x.s); }
	T abs(const P& x) { return sqrt(norm(x)); }
	T angle(const P& x) { return atan2(x.s,x.f); }
	P conj(const P& x) { return P(x.f,-x.s); }
	P perp(const P& x) { return P(-x.s,x.f); }
	P dir(T ang) { return P(cos(ang),sin(ang)); }
	
	P operator-(const P& l) { return P(-l.f,-l.s); }
	P operator+(const P& l, const P& r) { 
		return P(l.f+r.f,l.s+r.s); }
	P operator-(const P& l, const P& r) { 
		return P(l.f-r.f,l.s-r.s); }
	P operator*(const P& l, const T& r) { 
		return P(l.f*r,l.s*r); }
	P operator*(const T& l, const P& r) { return r*l; }
	P operator/(const P& l, const T& r) { 
		return P(l.f/r,l.s/r); }
	P operator*(const P& l, const P& r) { 
		return P(l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s); }
	P operator/(const P& l, const P& r) { 
		return l*conj(r)/norm(r); }
	P& operator+=(P& l, const P& r) { return l = l+r; }
	P& operator-=(P& l, const P& r) { return l = l-r; }
	P& operator*=(P& l, const T& r) { return l = l*r; }
	P& operator/=(P& l, const T& r) { return l = l/r; }
	P& operator*=(P& l, const P& r) { return l = l*r; }
	P& operator/=(P& l, const P& r) { return l = l/r; }
	
	P unit(const P& x) { return x/abs(x); }
	T dot(const P& a, const P& b) { return a.f*b.f+a.s*b.s; }
	T cross(const P& a, const P& b) { return a.f*b.s-a.s*b.f; }
	T cross(const P& p, const P& a, const P& b) {
		return cross(a-p,b-p); }
	P rotate(const P& a, T b) { return a*P(cos(b),sin(b)); }
	P reflect(const P& p, const P& a, const P& b) { 
		return a+conj((p-a)/(b-a))*(b-a); }
	P foot(const P& p, const P& a, const P& b) { 
		return (p+reflect(p,a,b))/(T)2; }
	bool onSeg(const P& p, const P& a, const P& b) { 
		return cross(a,b,p) == 0 && dot(p-a,p-b) <= 0; }
};
using namespace Point;
