/**
 * Description: Delaunay triangulation with 3D hull. 
 	* Fails when all points collinear.
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/cco08p6
 */

#include "../Primitives/Point.h"
#include "Hull3D.h"
#include "AngleCmp.h"

V<AR<P,3>> triHull(vP p) {
	V<P3> p3; V<AR<P,3>> res; each(x,p) p3.pb({x.f,x.s,norm(x)});
	bool ok = 0; each(t,p3) if (!coplanar(p3[0],p3[1],p3[2],t)) ok = 1;
	if (!ok) { // all points concyclic
		sort(1+all(p),[&p](P a, P b) { return cross(a-p[0],b-p[0]) > 0; });
		FOR(i,1,sz(p)-1) res.pb({p[0],p[i],p[i+1]});
	} else {
		#define nor(x) P(p3[x][0],p3[x][1])
		each(t,hull3dFast(p3)) 
			if (dot(cross(p3[t[0]],p3[t[1]],p3[t[2]]),{0,0,1}) < 0)
				res.pb({nor(t[0]),nor(t[2]),nor(t[1])});
	}
	return res;
}
