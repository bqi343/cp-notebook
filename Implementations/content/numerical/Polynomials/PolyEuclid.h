/**
 * Description: Euclidean Algorithm for polynomials using Half-GCD
 * Source:
	 * https://dl.acm.org/doi/pdf/10.1145/800125.804045
	 	* only works for normal remainder seqs
	 * https://pdfs.semanticscholar.org/a7e7/b01a3dd6ac0ec160b35e513c5efa38c2369e.pdf
	 	* complete solution
 * Time: O(N\log^2N)
 * Verification: https://judge.yosupo.jp/problem/inv_of_polynomials
 */

#include "PolyInv.h"

typedef array<poly,2> Arr;
typedef array<Arr,2> Mat;
const Mat ID = {Arr{poly{1},poly{}},Arr{poly{},poly{1}}};
Arr cut(Arr a, int k) { // decrease degrees by k
	F0R(i,2) a[i] = shift(a[i],-k);
	return a; }
Arr operator*(Mat a, Arr b) {
	Arr c; F0R(i,2) c[i] = REMZ(conv(a[i][0],b[0])+conv(a[i][1],b[1])); 
	return c; }
Mat operator*(Mat a, Mat b) { // multiply matrices
	Mat res; F0R(i,2) F0R(j,2) F0R(k,2) res[i][k] += conv(a[i][j],b[j][k]);
	return res; }

void step(Mat& m, Arr& a) { // perform one step of euclidean algo
	auto q = divi(a[0],a[1]); a = {a[1],REMZ(q.s)};
	m = {m[1],{REMZ(m[0][0]-conv(q.f,m[1][0])),REMZ(m[0][1]-conv(q.f,m[1][1]))}};
}
Mat hGCD(Arr a) { // half-gcd algo
	assert(sz(a[0]) > sz(a[1]) && sz(a[1])); // perform euclid steps until deg(a[1]) < m
	int m = sz(a[0])/2; if (sz(a[1]) <= m) return ID;
	Mat R = hGCD(cut(a,m)); a = R*a; if (sz(a[1]) <= m) return R;
	step(R,a); if (sz(a[1]) <= m) return R;
	int l = sz(a[0])-1, k = 2*m-l; return hGCD(cut(a,k))*R;
}
Mat euclid(Arr a) {
	assert(sz(a[0]) > sz(a[1]) && sz(a[1]));
	Mat m0 = hGCD(a); a = m0*a; if (!sz(a[1])) return m0;
	step(m0,a); if (!sz(a[1])) return m0;
	return euclid(a)*m0;
}
poly getInv(poly x, poly y) { // x*ans-1 is divisible by y
	Mat res = ID; Arr a = {x,y}; step(res,a); 
	if (sz(a[1])) res = euclid(a)*res; // same result as "while (sz(a[1])) step(res,a);"
	poly gcd = REMZ(conv(res[0][0],x)+conv(res[0][1],y));
	if (sz(gcd) != 1) { ps(-1); exit(0); } // gcd has deg > 0
	return REMZ(1/gcd[0]*res[0][0]);
}