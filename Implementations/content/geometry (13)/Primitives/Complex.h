/**
 * Description: Easy geo. 
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 * Verification: various
 */

#define x real()
#define y imag()
typedef ld T; // or db, not ll
int sgn(T a) { return (a>0)-(a<0); }
T sq(T a) { return a*a; }

namespace Point {
	typedef complex<T> P; typedef vector<P> vP;
	bool operator<(P l, P r) {
		return l.x != r.x ? l.x < r.x : l.y < r.y; }
	P perp(P p) { return P(-p.y,p.x); }
	P dir(T ang) { return polar((T)1,ang); }
	P unit(P p) { return p/abs(p); }
	T dot(P a, P b) { return a.x*b.x+a.y*b.y; }
	T cross(P a, P b) { return a.x*b.y-a.y*b.x; }
	T cross(P p, P a, P b) { return cross(a-p,b-p); }
	P reflect(P p,P a,P b) { return a+conj((p-a)/(b-a))*(b-a); }
	P foot(P p, P a, P b) { return (p+reflect(p,a,b))/(T)2; }
	bool onSeg(P p, P a, P b) { 
		return cross(a,b,p) == 0 && dot(p-a,p-b) <= 0; }
};
/// using namespace Point;

