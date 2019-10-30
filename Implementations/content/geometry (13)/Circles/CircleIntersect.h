/**
 * Description: circle intersection points (assuming they exist) and area
 * Source: Own
	* also see http://mathworld.wolfram.com/Circle-CircleIntersection.html
 * Verification:https://codefights.com/tournaments/s8thqrnQL2YPK7XQt/L
 */

#include "Circle.h"
 
P intersectPoint(circ x, circ y, int t = 0) { 
	T d = abs(x.f-y.f); // dist between centers
	T theta = acos((x.s*x.s+d*d-y.s*y.s)/(2*x.s*d)); // law of cosines
	P tmp = (y.f-x.f)/d*x.s;
	return x.f+tmp*dir(t == 0 ? theta : -theta);
}
T intersectArea(circ x, circ y) { // not thoroughly tested
	T d = abs(x.f-y.f), a = x.s, b = y.s; if (a < b) swap(a,b);
	if (d >= a+b) return 0;
	if (d <= a-b) return PI*b*b;
	auto ca = (a*a+d*d-b*b)/(2*a*d), cb = (b*b+d*d-a*a)/(2*b*d);
	auto s = (a+b+d)/2, h = 2*sqrt(s*(s-a)*(s-b)*(s-d))/d;
	return a*a*acos(ca)+b*b*acos(cb)-d*h;
}