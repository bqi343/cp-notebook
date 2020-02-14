/**
 * Description: 3D convex hull where not all points are coplanar. 
 	* Normals to returned faces point outwards.
 * Time: O(N^2)
 * Source: 
 	* KACTL
 	* https://codeforces.com/blog/entry/73366?#comment-575862
 	* https://code.google.com/codejam/contest/6314486/dashboard#s=p3
 		* make sure to deal with coplanar and use __int128 if necessary
 * Verification: https://www.spoj.com/problems/CH3D/
 */

#include "Point3D.h"

bool above(P3 a, P3 b, P3 c, P3 p) { // is p on or above plane
	return dot(cross(a,b,c),p-a) >= 0; }
typedef array<int,3> F; // face
vector<F> hull3d(vP3& p) { // make first four points form tetra
	int N = sz(p); FOR(i,1,N) if (p[0] != p[i]) swap(p[1],p[i]);
	FOR(i,2,N) if (!collinear(p[0],p[1],p[i])) swap(p[2],p[i]); 
	FOR(i,3,N)if (!coplanar(p[0],p[1],p[2],p[i]))swap(p[3],p[i]);
	vector<F> hull; 
	auto ad = [&](int a, int b, int c) { hull.pb({a,b,c}); };
	int a = 0, b = 1, c = 2, d = 3;
	if (above(p[a],p[b],p[c],p[d])) swap(c,d);
	ad(a,b,c); ad(b,a,d); ad(b,d,c), ad(d,a,c);
	vector<vector<bool>> in(N,vector<bool>(N));
	FOR(i,4,N) { // incremental construction
		vector<F> def, HULL; swap(hull,HULL);
		auto ins = [&](int a, int b, int c) {
			if (in[b][a]) in[b][a] = 0; // kill reverse face
			else in[a][b] = 1, ad(a,b,c);
		};
		trav(f,HULL) {
			int i0 = f[0], i1 = f[1], i2 = f[2]; 
			if (above(p[i0],p[i1],p[i2],p[i])) { 
				ins(i0,i1,i), ins(i1,i2,i), ins(i2,i0,i);
			} else def.pb({i0,i1,i2}); 
		}
		trav(t,hull) if (in[t[0]][t[1]]) 
			in[t[0]][t[1]] = 0, def.pb(t);
		swap(hull,def);
	}
	return hull;
}