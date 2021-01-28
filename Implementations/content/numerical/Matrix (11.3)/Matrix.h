/**
 * Description: 2D matrix operations. Use array instead of 
 	* vector when possible.
 * Source: KACTL
 * Verification: https://dmoj.ca/problem/si17c1p5, SPOJ MIFF
 */

#include "../../number-theory (11.1)/Modular Arithmetic/ModInt.h"

using T = mi;
using Mat = V<V<T>>;

Mat makeMat(int r, int c) { return Mat(r,vector<T>(c)); }
Mat makeId(int n) { 
	Mat m = makeMat(n,n);
	F0R(i,n) m[i][i] = 1;
	return m;
}
Mat& operator+=(Mat& a, const Mat& b) {
	assert(sz(a) == sz(b) && sz(a[0]) == sz(b[0]));
	F0R(i,sz(a)) F0R(j,sz(a[0])) a[i][j] += b[i][j];
	return a;
}
Mat& operator-=(Mat& a, const Mat& b) {
	assert(sz(a) == sz(b) && sz(a[0]) == sz(b[0]));
	F0R(i,sz(a)) F0R(j,sz(a[0])) a[i][j] -= b[i][j];
	return a;
}
Mat operator*(const Mat& a, const Mat& b) {
	int x = sz(a), y = sz(a[0]), z = sz(b[0]); 
	assert(y == sz(b)); Mat c = makeMat(x,z);
	F0R(i,x) F0R(j,y) F0R(k,z) c[i][k] += a[i][j]*b[j][k];
	return c;
}
Mat operator+(Mat a, const Mat& b) { return a += b; }
Mat operator-(Mat a, const Mat& b) { return a -= b; }
Mat& operator*=(Mat& a, const Mat& b) { return a = a*b; }
Mat pow(Mat m, ll p) {
	int n = sz(m); assert(n == sz(m[0]) && p >= 0);
	Mat res = makeId(n);
	for (; p; p /= 2, m *= m) if (p&1) res *= m;
	return res;
}