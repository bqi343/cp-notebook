/**
 * Description: half-plane intersection area
 * Time: O(N\log N)
 * Source: Own
 	* http://www.cs.umd.edu/class/spring2020/cmsc754/Lects/lect06-duality.pdf might be of interest
 * Verification:
	* https://open.kattis.com/problems/bigbrother 
	* (planes through two points with integer coordinates <= 10^7)
 */

#include "Point.h"

using Half = AR<T,3>; // half-plane
using vH = V<Half>;
P hp_point(const Half& h) { return {h[0],h[1]}; } // direction of half-plane
P isect(const Half& h0, const Half& h1) { // Cramer's rule to intersect half-planes
	AR<T,3> vals;
	FOR(i,-1,2) {
		int x = (i == 0 ? 2 : 0), y = (i == 1 ? 2 : 1);
		vals[1+i] = h0[x]*h1[y]-h0[y]*h1[x];
	}
	assert(vals[0] != 0); return {vals[1]/vals[0],vals[2]/vals[0]};
}
T eval(const Half& h, T x) { assert(h[1] != 0); // evaluate half-plane at x-coordinate
	return (h[2]-h[0]*x)/h[1]; }
T x_isect(const Half& h0, const Half& h1) { return isect(h0,h1).f; } // x-coordinate of intersection

vH construct_lower(P x, vH planes) { // similar to convex hull (by duality)
	sort(all(planes),[](const Half& a, const Half& b) {
		return cross(hp_point(a),hp_point(b)) > 0; });
	vH res{{1,0,x.f}}; // >= x.f
	planes.pb({-1,0,-x.s}); // <= x.s
	auto lst_x = [&](Half a, Half b) {
		if (cross(hp_point(a),hp_point(b)) == 0) // parallel half-planes, remove lower one
			return a[2]/a[1] <= b[2]/b[1] ? x.f : x.s;
		return x_isect(a,b);
	};
	each(t,planes) {
		while (sz(res) > 1 && lst_x(res.bk,t) <= lst_x(end(res)[-2],res.bk))
			res.pop_back();
		res.pb(t);
	}
	return res;
}

T isect_area(vH planes) {
	const T BIG = 1e9; P x{-BIG,BIG};
	planes.pb({0,1,-BIG}); // y >= -BIG
	planes.pb({0,-1,-BIG}); // -y >= -BIG
	vH upper, lower;
	each(t,planes) {
		if (t[1] == 0) { // vertical line
			T quo = t[2]/t[0];
			if (t[0] > 0) ckmax(x.f,quo);
			else ckmin(x.s,quo); // -x >=
		} else if (t[1] > 0) lower.pb(t);
		else upper.pb(t);
	}
	if (x.f >= x.s) return 0;
	lower = construct_lower(x,lower);

	each(t,upper) t[0] *= -1, t[1] *= -1; 
	upper = construct_lower({-x.s,-x.f},upper);
	each(t,upper) t[0] *= -1, t[1] *= -1;
	reverse(all(upper));
	int iu = 1, il = 1;
	T lst = x.f, lst_dif = eval(upper[1],lst)-eval(lower[1],lst);
	T ans = 0;
	while (iu < sz(upper)-1 && il < sz(lower)-1) { // sweep vertical line through lower and upper hulls
		T nex_upper = x_isect(upper[iu],upper[iu+1]);
		T nex_lower = x_isect(lower[il],lower[il+1]);
		T nex = min(nex_upper,nex_lower);
		T nex_dif = eval(upper[iu],nex)-eval(lower[il],nex);
		auto avg_val = [](T a, T b) -> T {
			if (a > b) swap(a,b);
			if (b <= 0) return 0;
			if (a >= 0) return (a+b)/2;
			return b/(b-a)*b/2;
		};
		ans += (nex-lst)*avg_val(lst_dif,nex_dif);
		assert(x.f <= nex && nex <= x.s);
		lst = nex, lst_dif = nex_dif;
		iu += lst == nex_upper;
		il += lst == nex_lower;
	}
	return ans;
}

Half plane_right(P a, P b) { // half-plane to right of a -> b
	return {b.s-a.s,a.f-b.f,(b.s-a.s)*a.f+(a.f-b.f)*a.s}; }
Half plane_through(P p, P dir) { // half-plane through p in direction dir
	return {dir.f,dir.s,dot(p,dir)}; }
