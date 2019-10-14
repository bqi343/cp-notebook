/*
 * Description: Delaunay Triangulation w/ Bowyer-Watson in O(n^2logn)
 * Source: Own
 * Verification: ICPC WF 2018 Panda Preserve
 */

namespace Delaunay {
	// use __int128 for better precision, if possible
	ld cross(cd b, cd c) { return (conj(b)*c).imag(); }
	ld cross(cd a, cd b, cd c) { return cross(b-a,c-a); }

	bool inCircle (cd a, cd b, cd c, cd d) {
		a -= d, b -= d, c -= d;
		ld x = norm(a)*cross(b,c)+norm(b)*cross(c,a)
				+norm(c)*cross(a,b);
		if (cross(a,b,c) < 0) x *= -1;
		return x > 0;
	}

	vector<array<int,3>> triangulate(vcd v) {
		// works with cyclic quads
		// not when all points are collinear!
		// creates super-triangle, adjusts as necessary

		v.pb(cd(-1e5,-1e5)); v.pb(cd(1e5,0)); v.pb(cd(0,1e5)); // might not be sufficiently large

		vector<array<int,3>> ret;
		ret.pb({sz(v)-3,sz(v)-2,sz(v)-1});

		F0R(i,sz(v)-3) {
			map<pi,int> m;
			vector<array<int,3>> tmp;
			trav(a,ret) {
				if (inCircle(v[a[0]],v[a[1]],v[a[2]],v[i]))
					m[{a[0],a[1]}] ++, m[{a[1],a[2]}] ++, m[{a[0],a[2]}] ++;
				else tmp.pb(a);
			}
			trav(a,m) if (a.s == 1) {
				array<int,3> x = {a.f.f,a.f.s,i}; sort(all(x));
				tmp.pb(x);
			}
			ret = tmp;
		}
		vector<array<int,3>> tmp;
		trav(a,ret) if (a[2] < sz(v)-3) tmp.pb(a);
		return tmp;
	}

	void print(vcd x) { // produces asymptote code
		cout << "[asy]\n";
		cout << "pair[] A = {";
		bool done = 0;
		trav(a,x) {
			if (done) cout << ",";
			cout << a; done = 1;
		}
		cout << "};\n";

		cout << "for (int i = 0; i < " << sz(x) << "; ++i) {\n\tdot(A[i]);\n}\n";

		trav(b,triangulate(x)) cout << "draw(A[" << b[0] << "]--A[" << b[1] << "]--A[" << b[2] << "]--cycle);\n";
		cout << "[/asy]\n";
	}
};
