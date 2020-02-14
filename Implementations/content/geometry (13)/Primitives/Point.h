/**
 * Description: Use in place of \texttt{complex<T>}.
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 * Verification: various
 */

typedef ld T;
int sgn(T a) { return (a>0)-(a<0); }
T sq(T a) { return a*a; }

namespace Point {
	typedef pair<T,T> P; typedef vector<P> vP;
	T norm(const P& p) { return sq(p.f)+sq(p.s); }
	T abs(const P& p) { return sqrt(norm(p)); }
	T arg(const P& p) { return atan2(p.s,p.f); }
	P conj(const P& p) { return P(p.f,-p.s); }
	P perp(const P& p) { return P(-p.s,p.f); }
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
	
	P unit(const P& p) { return p/abs(p); }
	T dot(const P& a, const P& b) { return a.f*b.f+a.s*b.s; }
	T cross(const P& a, const P& b) { return a.f*b.s-a.s*b.f; }
	T cross(const P& p, const P& a, const P& b) {
		return cross(a-p,b-p); }
	P reflect(const P& p, const P& a, const P& b) { 
		return a+conj((p-a)/(b-a))*(b-a); }
	P foot(const P& p, const P& a, const P& b) { 
		return (p+reflect(p,a,b))/(T)2; }
	bool onSeg(const P& p, const P& a, const P& b) { 
		return cross(a,b,p) == 0 && dot(p-a,p-b) <= 0; }
	ostream& operator<<(ostream& os, const P& p) {
		return os << "(" << p.f << "," << p.s << ")"; }
};
using namespace Point;