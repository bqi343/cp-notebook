/**
 * Description: misc operations with circles
 * Source: Own
 	* also see http://mathworld.wolfram.com/Circle-CircleIntersection.html
 * Verification: USACO Laser Cows, https://codefights.com/tournaments/s8thqrnQL2YPK7XQt/L
 */

using namespace point;

namespace circle {
	typedef pair<P,T> circ;
 
	bool on(circ x, P y) { return abs(y-x.f) == x.s; }
	bool in(circ x, P y) {  return abs(y-x.f) <= x.s; }
	T arcLength(circ x, P a, P b) {
	    P d = (a-x.f)/(b-x.f);
	    return x.s*acos(d.f);
	}
	void pr(const circ& x) { pr(mp(x.f,x.s)); }
	 
	P intersect(circ x, circ y, int t = 0) { 
	    T d = abs(x.f-y.f); // distance between centers
	    T theta = acos((x.s*x.s+d*d-y.s*y.s)/(2*x.s*d)); // law of cosines
	    P tmp = (y.f-x.f)/d*x.s;
	    return x.f+tmp*dir(t == 0 ? theta : -theta);
	}
	 
	P tangent(P x, circ y, int t = 0) {
	    y.s = abs(y.s); // abs needed because internal calls y.s < 0
	    if (y.s == 0) return y.f;
	    T d = abs(x-y.f);
	    P a = pow(y.s/d,2)*(x-y.f)+y.f;
	    P b = sqrt(d*d-y.s*y.s)/d*y.s*unit(x-y.f)*dir(PI/2); 
	    return t == 0 ? a+b : a-b;
	}
	 
	vector<pair<P,P>> external(circ x, circ y) { // external tangents
	    vector<pair<P,P>> v; 
	    if (x.s == y.s) {
	        P tmp = unit(x.f-y.f)*x.s*dir(PI/2);
	        v.pb(mp(x.f+tmp,y.f+tmp));
	        v.pb(mp(x.f-tmp,y.f-tmp));
	    } else {
	        P p = (y.s*x.f-x.s*y.f)/(y.s-x.s);
	        F0R(i,2) v.pb({tangent(p,x,i),tangent(p,y,i)});
	    }
	    return v;
	}
	 
	vector<pair<P,P>> internal(circ x, circ y) { // internal tangents
	    x.s *= -1; return external(x,y);
	}
}

using namespace circle;