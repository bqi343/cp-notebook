/**
 * Description: Use in place of \texttt{complex<T>}.
 * Source: http://codeforces.com/blog/entry/22175
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/geometry/Point.h
 * Verification: various
 */

using T = ld;
int sgn(T a) { return (a>0)-(a<0); }
T sq(T a) { return a*a; }

typedef pair<T,T> P; typedef vector<P> vP;
T norm(P p) { return sq(p.f)+sq(p.s); }
T abs(P p) { return sqrt(norm(p)); }
T arg(P p) { return atan2(p.s,p.f); }
P conj(P p) { return P(p.f,-p.s); }
P perp(P p) { return P(-p.s,p.f); }
P operator+(P l, P r) { return P(l.f+r.f,l.s+r.s); }
P operator-(P l, P r) { return P(l.f-r.f,l.s-r.s); }
P operator*(P l, T r) { return P(l.f*r,l.s*r); }
P operator/(P l, T r) { return P(l.f/r,l.s/r); }
P operator*(P l, P r) { // complex # multiplication 
	return P(l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s); }
P operator/(P l, P r) { return l*conj(r)/norm(r); }

P unit(P p) { return p/abs(p); }
T dot(P a, P b) { return a.f*b.f+a.s*b.s; }
T cross(P a, P b) { return a.f*b.s-a.s*b.f; }
T cross(P p, P a, P b) { return cross(a-p,b-p); }
P reflect(P p, P a, P b) { 
	return a+conj((p-a)/(b-a))*(b-a); }
P foot(P p, P a, P b) { return (p+reflect(p,a,b))/(T)2; }
bool onSeg(P p, P a, P b) { 
	return cross(a,b,p) == 0 && dot(p-a,p-b) <= 0; }
ostream& operator<<(ostream& os, P p) {
	return os << "(" << p.f << "," << p.s << ")"; }