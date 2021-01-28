/**
 * Description: surface area and volume of polyhedron,
 	* normals to faces must point outwards
 * Source: KACTL
 * Verification: See Hull3D
 */

#include "Hull3D.h"

pair<T,T> SaVol(vP3 p, V<F> faces) {
	T s = 0, v = 0; 
	each(i,faces) {
		P3 a = p[i[0]], b = p[i[1]], c = p[i[2]];
		s += abs(cross(a,b,c)); v += dot(cross(a,b),c);
	}
	return {s/2,v/6};
}
