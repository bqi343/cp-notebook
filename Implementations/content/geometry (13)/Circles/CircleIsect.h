/**
 * Description: Circle intersection points and intersection area. 
 	* Tangents will be returned twice.
 * Source: Own
	* also see http://mathworld.wolfram.com/Circle-CircleIntersection.html
 * Verification:https://codefights.com/tournaments/s8thqrnQL2YPK7XQt/L
 */

#include "Circle.h"

vP isect(const Circ& x, const Circ& y) { // precondition: x != y
	T d = abs(x.f-y.f), a = x.s, b = y.s; 
	if (sgn(d) == 0) { assert(a != b); return {}; }
	T C = (a*a+d*d-b*b)/(2*a*d); 
	if (abs(C) > 1+EPS) return {};
	T S = sqrt(max(1-C*C,(T)0)); P tmp = (y.f-x.f)/d*x.s;
	return {x.f+tmp*P(C,S),x.f+tmp*P(C,-S)};
}
vP isect(const Circ& x, const Line& y) {
	P c = foot(x.f,y); T sq_dist = sq(x.s)-norm(x.f-c);
	if (sgn(sq_dist) < 0) return {};
	P offset = unit(y.s-y.f)*sqrt(max(sq_dist,T(0)));
	return {c+offset,c-offset};
}
T isect_area(Circ x, Circ y) { // not thoroughly tested
	T d = abs(x.f-y.f), a = x.s, b = y.s; if (a < b) swap(a,b);
	if (d >= a+b) return 0;
	if (d <= a-b) return PI*b*b;
	T ca = (a*a+d*d-b*b)/(2*a*d), cb = (b*b+d*d-a*a)/(2*b*d);
	T s = (a+b+d)/2, h = 2*sqrt(s*(s-a)*(s-b)*(s-d))/d;
	return a*a*acos(ca)+b*b*acos(cb)-d*h;
}