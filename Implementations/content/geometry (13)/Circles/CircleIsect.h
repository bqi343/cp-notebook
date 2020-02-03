/**
 * Description: circle intersection points and intersection area
 * Source: Own
	* also see http://mathworld.wolfram.com/Circle-CircleIntersection.html
 * Verification:https://codefights.com/tournaments/s8thqrnQL2YPK7XQt/L
 */

#include "Circle.h"

vP isectPoint(circ x, circ y) { 
	T d = abs(x.f-y.f), a = x.s, b = y.s; 
	if (d == 0) { assert(a != b); return {}; }
	T C = (a*a+d*d-b*b)/(2*a*d); if (abs(C) > 1) return {};
	T S = sqrt(1-C*C); P tmp = (y.f-x.f)/d*x.s;
	return {x.f+tmp*P(C,S),x.f+tmp*P(C,-S)};
}
T isectArea(circ x, circ y) { // not thoroughly tested
	T d = abs(x.f-y.f), a = x.s, b = y.s; if (a < b) swap(a,b);
	if (d >= a+b) return 0;
	if (d <= a-b) return PI*b*b;
	auto ca = (a*a+d*d-b*b)/(2*a*d), cb = (b*b+d*d-a*a)/(2*b*d);
	auto s = (a+b+d)/2, h = 2*sqrt(s*(s-a)*(s-b)*(s-d))/d;
	return a*a*acos(ca)+b*b*acos(cb)-d*h;
}
