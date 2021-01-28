/**
 * Description: Incremental 3D convex hull where not all points 
 	* are coplanar. Normals to returned faces point outwards. 
 	* If coordinates are ints at most $B$ then \texttt{T} 
 	* should be large enough to support ints on the order 
 	* of $B^3$.
 * Time: O(N^2), O(N\log N)
 * Source: 
 	* KACTL
 	* https://codeforces.com/blog/entry/73366?#comment-575862 (mango_lassi)
 	* https://codeforces.com/blog/entry/81768 (Monogon)
 	* https://people.csail.mit.edu/indyk/6.838-old/handouts/lec10.pdf (presentation)
 	* https://www2.cs.duke.edu/courses/spring07/cps296.2/papers/clarkson-shor.pdf
 * Verification: https://www.spoj.com/problems/CH3D/
 	* https://code.google.com/codejam/contest/6314486/dashboard#s=p3
 */

// using T = ll;
T above(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return DC(a,b,c,p) > 0; } // is p strictly above plane
void prep(vP3& p) { // rearrange points such that
	int num = 1; // first four are not coplanar
	FOR(i,1,sz(p)) 
		if (num == 1) {
			if (p[0] != p[i]) swap(p[1],p[i]), num ++;
		} else if (num == 2) {
			if (!collinear(p[0],p[1],p[i])) 
				swap(p[2],p[i]), num ++;
		} else if (num == 3) {
			if (!coplanar(p[0],p[1],p[2],p[i]))
				swap(p[3],p[i]), num ++;
		}
	assert(num == 4);
}

using F = AR<int,3>; // face
V<F> hull3d(vP3& p) { // order of points is changed s.t. first four points form tetra
	prep(p); int N = sz(p); V<F> hull; // triangle for each face
	auto ad = [&](int a, int b, int c) { hull.pb({a,b,c}); }; // add a new face to hull
	ad(0,1,2), ad(0,2,1); // initialize hull as first three points
	V<vb> in(N,vb(N)); // is zero before each iteration
	FOR(i,3,N) { // incremental construction
		V<F> def, HULL; swap(hull,HULL); // HULL now contains old hull
		auto ins = [&](int a, int b, int c) {
			if (in[b][a]) in[b][a] = 0; // kill reverse face
			else in[a][b] = 1, ad(a,b,c);
		};
		each(f,HULL) {
			if (above(p[f[0]],p[f[1]],p[f[2]],p[i]))  // recalc all faces such that point is above face
				F0R(j,3) ins(f[j],f[(j+1)%3],i);
			else def.pb(f); 
		}
		each(t,hull) if (in[t[0]][t[1]]) // edge is exposed, add a new face
			in[t[0]][t[1]] = 0, def.pb(t);
		swap(hull,def);
	}
	return hull;
}
V<F> hull3dFast(vP3& p) { // order of points is changed s.t. first four points form tetra
	shuffle(all(p),rng); prep(p); int N = sz(p); V<F> hull; 
	vb active; V<vi> rvis; V<AR<pi,3>> other; // whether face is active
	// points visible from each face, other face adjacent to each edge of face
	V<vi> vis(N); // faces visible from each point
	auto ad = [&](int a, int b, int c) { 
		hull.pb({a,b,c}); active.pb(1); rvis.eb(); other.eb(); };
	auto ae = [&](int a, int b) { vis[b].pb(a), rvis[a].pb(b); };
	auto abv = [&](int a, int b) {
		F f = hull[a]; return above(p[f[0]],p[f[1]],p[f[2]],p[b]); };
	auto edge = [&](pi e) -> pi { return {hull[e.f][e.s],hull[e.f][(e.s+1)%3]}; };
	auto glue = [&](pi a, pi b) { // link two faces by an edge
		pi x = edge(a); assert(edge(b) == mp(x.s,x.f));
		other[a.f][a.s] = b, other[b.f][b.s] = a;
	}; 
	ad(0,1,2), ad(0,2,1); if (abv(1,3)) swap(p[1],p[2]); // ensure face 0 is removed when i=3
	F0R(i,3) glue({0,i},{1,2-i});
	FOR(i,3,N) ae(abv(1,i),i); // those that are coplanar go in rvis[0]
	vi label(N,-1);
	FOR(i,3,N) { // incremental construction
		vi rem; each(t,vis[i]) if (active[t]) active[t] = 0, rem.pb(t);
		if (!sz(rem)) continue; // hull unchanged
		int st = -1; 
		each(r,rem) F0R(j,3) {
			int o = other[r][j].f;
			if (active[o]) { // create new face!
				int a,b; tie(a,b) = edge({r,j}); ad(a,b,i); st = a;
				int cur = sz(rvis)-1; label[a] = cur; 
				vi tmp; set_union(all(rvis[r]),all(rvis[o]),back_inserter(tmp)); 
				// merge sorted vectors ignoring duplicates
				each(x,tmp) if (abv(cur,x)) ae(cur,x);
				// if no rounding errors then guaranteed that only x > i matters
				glue({cur,0},other[r][j]); // glue old face with new face
			}
		}
		for (int x = st, y; ; x = y) { // glue new faces together
			int X = label[x]; glue({X,1},{label[y=hull[X][1]],2});
			if (y == st) break;
		}
	}
	V<F> ans; F0R(i,sz(hull)) if (active[i]) ans.pb(hull[i]);
	return ans;
}
