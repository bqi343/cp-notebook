/**
 * Description: Basic 3D geometry. 
 * Source: Own
 * Verification: (haven't done much 3D geo yet)
	* AMPPZ 2011 Cross Spider
	* https://atcoder.jp/contests/JAG2013Spring/tasks/icpc2013spring_h
	* https://codeforces.com/gym/102040 - I
	* https://codeforces.com/gym/102452/problem/F
 */

#include "../Primitives/Point.h"

/**
using T = ld;
int sgn(T x) { return (x>0)-(x<0); }
T sq(T x) { return x*x; }
*/

typedef array<T,3> P3;
typedef array<P3,3> tri;
typedef vector<P3> vP3;
T norm(const P3& x) { 
	T sum = 0; F0R(i,3) sum += sq(x[i]);
	return sum; }
T abs(const P3& x) { return sqrt(norm(x)); }

P3& operator+=(P3& l, const P3& r) { F0R(i,3) l[i] += r[i]; 
	return l; }
P3& operator-=(P3& l, const P3& r) { F0R(i,3) l[i] -= r[i]; 
	return l; }
P3& operator*=(P3& l, const T& r) { F0R(i,3) l[i] *= r; 
	return l; }
P3& operator/=(P3& l, const T& r) { F0R(i,3) l[i] /= r; 
	return l; }
P3 operator-(P3 l) { l *= -1; return l; }
P3 operator+(P3 l, const P3& r) { return l += r; }
P3 operator-(P3 l, const P3& r) { return l -= r; }
P3 operator*(P3 l, const T& r) { return l *= r; }
P3 operator*(const T& r, const P3& l) { return l*r; }
P3 operator/(P3 l, const T& r) { return l /= r; }

P3 unit(const P3& x) { return x/abs(x); }
T dot(const P3& a, const P3& b) { 
	T sum = 0; F0R(i,3) sum += a[i]*b[i]; 
	return sum; }
P3 cross(const P3& a, const P3& b) {
	return {a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],
			a[0]*b[1]-a[1]*b[0]}; }
P3 cross(const P3& a, const P3& b, const P3& c) {
	return cross(b-a,c-a); }
P3 perp(const P3& a, const P3& b, const P3& c) {
	return unit(cross(a,b,c)); }

bool isMult(const P3& a, const P3& b) { // for long longs
	P3 c = cross(a,b); F0R(i,sz(c)) if (c[i] != 0) return 0; 
	return 1; }
bool collinear(const P3& a, const P3& b, const P3& c) { 
	return isMult(b-a,c-a); }

T DC(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return dot(cross(a,b,c),p-a); }
bool coplanar(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return DC(a,b,c,p) == 0; }
bool op(const P3& a, const P3& b) { 
	int ind = 0; // going in opposite directions?
	FOR(i,1,3) if (std::abs(a[i]*b[i])>std::abs(a[ind]*b[ind])) 
		ind = i;
	return a[ind]*b[ind] < 0;
}
// coplanar points, b0 and b1 on opposite sides of a0-a1?
bool opSide(const P3&a,const P3&b,const P3&c,const P3&d) { 
	return op(cross(a,b,c),cross(a,b,d)); }
// coplanar points, is a in triangle b
bool inTri(const P3& a, const tri& b) { 
	F0R(i,3)if(opSide(b[i],b[(i+1)%3],b[(i+2)%3],a))return 0;
	return 1; }

// point-seg dist
T psDist(const P3&p,const P3&a,const P3&b) { 
	if (dot(a-p,a-b) <= 0) return abs(a-p);
	if (dot(b-p,b-a) <= 0) return abs(b-p);
	return abs(cross(p,a,b))/abs(a-b);
}
// projection onto line
P3 foot(const P3& p, const P3& a, const P3& b) { 
	P3 d = unit(b-a); return a+dot(p-a,d)*d; }
// rotate p about axis
P3 rotAxis(const P3& p, const P3& a, const P3& b, T theta) {
	P3 dz = unit(b-a), f = foot(p,a,b); 
	P3 dx = p-f, dy = cross(dz,dx);
	return f+cos(theta)*dx+sin(theta)*dy;
}
// projection onto plane
P3 foot(const P3& a, const tri& b) {
	P3 c = perp(b[0],b[1],b[2]);
	return a-c*(dot(a,c)-dot(b[0],c)); }
// line-plane intersection
P3 lpIntersect(const P3&a0,const P3&a1,const tri&b) { 
	P3 c = unit(cross(b[2]-b[0],b[1]-b[0]));
	T x = dot(a0,c)-dot(b[0],c), y = dot(a1,c)-dot(b[0],c);
	return (y*a0-x*a1)/(y-x);
}