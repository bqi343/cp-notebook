/**
 * Description: Top-bottom convex hull
 * Time: O(N\log N)
 * Source: Wikibooks, KACTL
 * Verification:
	* https://open.kattis.com/problems/convexhull
	* https://open.kattis.com/problems/roberthood
 */

// typedef ll T;

using namespace Point;

pair<vi,vi> ulHull(const vP& P) {
	vi p(sz(P)), u, l; iota(all(p), 0);
	sort(all(p), [&P](int a, int b) { return P[a] < P[b]; });
	trav(i,p) {
		#define ADDP(C, cmp) while (sz(C) > 1 && cross(\
			P[C[sz(C)-2]],P[C.back()],P[i]) cmp 0) C.pop_back(); C.pb(i);
		ADDP(u, >=); ADDP(l, <=);
	}
	return {u,l};
}

vi hullInd(const vP& P) {
	vi u,l; tie(u,l) = ulHull(P);
	if (sz(l) <= 1) return l;
	if (P[l[0]] == P[l[1]]) return {0};
	l.insert(end(l),rbegin(u)+1,rend(u)-1); return l;
}
vP hull(const vP& P) {
	vi v = hullInd(P);
	vP res; trav(t,v) res.pb(P[t]);
	return res;
}

ld diameter(vP P) { // rotating calipers
	P = hull(P);
	int n = sz(P), ind = 1; ld ans = 0;
	F0R(i,n) 
		for (int j = (i+1)%n;;ind = (ind+1)%n) {
			ckmax(ans,abs(P[i]-P[ind]));
			if (cross(P[j]-P[i],P[(ind+1)%n]-P[ind]) <= 0) break;
		}
	return ans;
}