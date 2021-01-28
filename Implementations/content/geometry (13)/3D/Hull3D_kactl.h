/**
 * Description: 3D convex hull where no four points coplanar, polyedron volume
 * Time: O(N^2)
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/starsinacan
 */

#include "Point3D.h"

struct ED {
	void ins(int x) { (a == -1 ? a : b) = x; }
	void rem(int x) { (a == x ? a : b) = -1; }
	int cnt() { return (a != -1)+(b != -1); }
	int a, b;
};
struct F { P3 q; int a, b, c; };

vector<F> hull3d(const vP3& A) { 
	assert(sz(A) >= 4);
	vector<vector<ED>> E(sz(A), vector<ED>(sz(A), {-1, -1}));
	#define E(x,y) E[f.x][f.y]
	vector<F> FS; // faces
	auto mf = [&](int i, int j, int k, int l) { // make face
		P3 q = cross(A[j]-A[i],A[k]-A[i]);
		if (dot(q,A[l]) > dot(q,A[i])) q *= -1; // make sure q points outward
		F f{q, i, j, k};
		E(a,b).ins(k); E(a,c).ins(j); E(b,c).ins(i);
		FS.pb(f);
	};
	F0R(i,4) FOR(j,i+1,4) FOR(k,j+1,4) mf(i, j, k, 6-i-j-k);
	FOR(i,4,sz(A)) {
		F0R(j,sz(FS)) {
			F f = FS[j];
			if (dot(f.q,A[i]) > dot(f.q,A[f.a])) { // face is visible, remove edges
				E(a,b).rem(f.c), E(a,c).rem(f.b), E(b,c).rem(f.a);
				swap(FS[j--], FS.bk);
				FS.pop_back();
			}
		}
		F0R(j,sz(FS)) { // add faces with new point
			F f = FS[j];
			#define C(a, b, c) if (E(a,b).cnt() != 2) mf(f.a, f.b, i, f.c);
			C(a, b, c); C(a, c, b); C(b, c, a);
		}
	}
	each(it, FS) if (dot(cross(A[it.b]-A[it.a],A[it.c]-A[it.a]),it.q) <= 0) 
		swap(it.c, it.b);
	return FS;
} 

T signedPolyVolume(const vP3& p, const vector<F>& trilist) {
	T v = 0;
	each(i,trilist) v += dot(cross(p[i.a],p[i.b]),p[i.c]);
	return v/6;
}
