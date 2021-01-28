/**
 * Description: Bowyer-Watson where not all points collinear. 
 	* Works for $|x|,|y|\le 10^4,$ assuming that all circumradii 
 	* in final triangulation are $\ll 10^9.$
 * Time: O(N^2\log N)
 * Source: Own
 * Verification: 
	* ICPC WF 2018 Panda Preserve
	* https://dmoj.ca/problem/cco08p6 (32/37)
 */

#include "DelaunayFast.h"

const T BIG = 1e9; // >>(10^4)^2
vector<array<int,3>> triIncrement(vP v) {
	v.pb({-BIG,-BIG}); v.pb({BIG,0}); v.pb({0,BIG});
	vector<array<int,3>> ret, tmp;
	ret.pb({sz(v)-3,sz(v)-2,sz(v)-1});
	F0R(i,sz(v)-3) {
		map<pi,int> m; 
		each(a,ret) {
			if (inCircle(v[i],v[a[0]],v[a[1]],v[a[2]]))
				m[{a[0],a[1]}]++, m[{a[1],a[2]}]++, m[{a[0],a[2]}]++;
			else tmp.pb(a);
		}
		each(a,m) if (a.s == 1) {
			array<int,3> x = {a.f.f,a.f.s,i}; 
			sort(all(x)); tmp.pb(x);
		}
		swap(ret,tmp); tmp.clear();
	}
	each(a,ret) if (a[2] < sz(v)-3) tmp.pb(a);
	return tmp;
}
/**void printAsy(vP x) { // produces asymptote code
	ps("[asy]");
	ps("pair[] A = {");
	F0R(i,sz(x)) {
		if (i) pr(",");
		pr(x[i]); 
	}
	ps("};");
	ps("for (int i = 0; i < ",sz(x),"; ++i) {\n\tdot(A[i]);\n}");
	each(b,triangulate(x)) 
		ps("draw(A[",b[0],"]--A[",b[1],"]--A[",b[2],"]--cycle);");
	ps("[/asy]");
}*/
