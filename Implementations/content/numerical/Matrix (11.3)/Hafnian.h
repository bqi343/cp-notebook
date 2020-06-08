/**
 * Description: Counts number of perfect matchings given adjacency matrix,
 	* which is symmetric and whose main diagonal contains only 0s. Must
 	* have an even # of vertices. Uses PIE.
 * Time: O(N^42^{N/2}), <2s for $N=38$.
 * Source: 
 	* https://dl.acm.org/doi/pdf/10.5555/2095116.2095189
 	* https://judge.yosupo.jp/submission/9282
 */

#include "../../number-theory (11.1)/Modular Arithmetic/ModInt.h"

struct Haf {
	int h; // = n/2+1
	void ad(vmi& x, const vmi& a, const vmi& b) { // all have size h
		F0R(i,h) F0R(j,h-1-i) x[i+j+1] += a[i]*b[j]; }
	vmi solve(const vector<vector<vmi>>& v) { // keep removing last two verts
		vmi ans(h); if (!sz(v)) { ans[0] = 1; return ans; }
		int m = sz(v)-2; auto V = v; V.rsz(m); vmi zero = solve(V);
		F0R(i,m) F0R(j,i) {
			ad(V[i][j],v[m][i],v[m+1][j]);
			ad(V[i][j],v[m+1][i],v[m][j]);
		} // do inclusion-exclusion
		vmi one = solve(V); F0R(i,h) ans[i] += one[i]-zero[i]; 
		ad(ans,one,v[m+1][m]); return ans;
	} // include edge connecting m w/ m+1
	mi calc(vector<vmi> m) { // m is adj matrix
		int n = sz(m); assert(n%2 == 0); h = n/2+1; 
		vector<vector<vmi>> v(n);
		F0R(i,n) { // only keep track of lower triangle
			v[i].rsz(i);
			F0R(j,i) v[i][j] = vmi(h), v[i][j][0] = m[i][j];
		}
		return solve(v).bk; // take term with degree n/2
	}
};