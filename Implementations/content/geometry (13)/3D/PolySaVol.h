/**
 * Description: surface area and volume of polyhedron,
 	* normals to faces must point outwards
 */

#include "Hull3D.h"

pair<T,T> SaVol(vP3 p, vector<F> faces) {
	T s = 0, v = 0; 
	trav(i,faces) {
		s += abs(cross(p[i[0]],p[i[1]],p[i[2]]));
		v += dot(cross(p[i[0]],p[i[1]]),p[i[2]]);
	}
	return {s/2,v/6};
}