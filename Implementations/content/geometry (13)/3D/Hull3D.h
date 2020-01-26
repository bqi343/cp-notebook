/**
 * Description: 3D convex hull and polyedron surface area/volume.
 	* Not all points should be coplanar.
 * Time: O(N^2\log N)
 * Source: 
 	* KACTL
 	* https://codeforces.com/blog/entry/73366?#comment-575862
 * Verification: https://www.spoj.com/problems/CH3D/

 */

#include "Point3D.h"

bool above(P3 a, P3 b, P3 c, P3 p) { // is p on or above plane
	return dot(cross(a,b,c),p-a) >= 0; }

typedef array<int,3> F; // face
vector<F> hull3d(vP3& p) { // make first four points form tetra
	FOR(i,1,sz(p)) if (p[0] != p[i]) swap(p[1],p[i]);
	FOR(i,2,sz(p)) if (!collinear(p[0],p[1],p[i])) 
		swap(p[2],p[i]); 
	FOR(i,3,sz(p)) if (!coplanar(p[0],p[1],p[2],p[i]))
		swap(p[3],p[i]);
	set<F> hull;
	auto ins = [&](int a, int b, int c) {
		F v = {a,b,c}; rotate(begin(v),max_element(all(v)),end(v));
		F V = {v[0],v[2],v[1]};  // reverse face
		if (hull.count(V)) hull.erase(V); // cancels out
		else hull.insert(v); // insert new face
	};
	int a = 0, b = 1, c = 2, d = 3;
	if (above(p[a],p[b],p[c],p[d])) swap(c,d);
	ins(a,b,c); ins(b,a,d); ins(c,b,d); ins(a,c,d); 
	FOR(i,4,sz(p)) { // incremental construction
		set<F> HULL; swap(hull,HULL);
		trav(f,HULL) {
			int i0 = f[0], i1 = f[1], i2 = f[2]; 
			if (above(p[i0],p[i1],p[i2],p[i])) { 
				ins(i0,i1,i); ins(i1,i2,i); ins(i2,i0,i);
			} else hull.insert({i0,i1,i2}); // face remains
		}
	}
	return vector<F>(all(hull));
}
pair<T,T> SaVol(const vP3& p, const vector<F>& faces) {
	T s = 0, v = 0; // surface area, volume
	trav(i,faces) {
		s += abs(cross(p[i[0]],p[i[1]],p[i[2]]));
		v += dot(cross(p[i[0]],p[i[1]]),p[i[2]]);
	}
	return {s/2,v/6};
}