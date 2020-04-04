/**
 * Description: surface area and volume of polyhedron,
 	* normals to faces must point outwards
 */

#include "Hull3D.h"

pair<T,T> SaVol(vP3 p, vector<F> faces) {
	T s = 0, v = 0; 
	trav(i,faces) {
		P3 a = p[i[0]], b = p[i[1]], c = p[i[2]];
		s += abs(cross(a,b,c)); v += dot(cross(a,b),c);
	}
	return {s/2,v/6};
}