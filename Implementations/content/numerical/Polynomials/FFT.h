/**
 * Description: multiply two polynomials
 * Time: O(N\log N)
 * Source: KACTL, https://cp-algorithms.com/algebra/fft.html
 * Verification: 
	* SPOJ polymul, CSA manhattan, CF Perfect Encoding
	* http://codeforces.com/contest/632/problem/E
 */

#include "Modular.h"

typedef complex<db> cd;
const int MOD = (119 << 23) + 1, root = 3; // = 998244353
// NTT: For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

constexpr int size(int s) { return s > 1 ? 32-__builtin_clz(s-1) : 0; }
void genRoots(vmi& roots) { // primitive n-th roots of unity
	int n = sz(roots); mi r = pow(mi(root),(MOD-1)/n);
	roots[0] = 1; FOR(i,1,n) roots[i] = roots[i-1]*r;
}
void genRoots(vcd& roots) { // change cd to complex<double> instead?
	int n = sz(roots); double ang = 2*PI/n;
	F0R(i,n) roots[i] = cd(cos(ang*i),sin(ang*i)); // is there a way to do this more quickly?
}

template<class T> void fft(vector<T>& a, const vector<T>& roots, bool inv = 0) {
	int n = sz(a);
	for (int i = 1, j = 0; i < n; i++) { // sort by reverse bit representation
		int bit = n >> 1;
		for (; j&bit; bit >>= 1) j ^= bit;
		j ^= bit; if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) 
		for (int i = 0; i < n; i += len) 
			F0R(j,len/2) {
				int ind = n/len*j; if (inv && ind) ind = n-ind;
				auto u = a[i+j], v = a[i+j+len/2]*roots[ind];
				a[i+j] = u+v, a[i+j+len/2] = u-v;
			}
	if (inv) { T i = T(1)/T(n); trav(x,a) x *= i; }
}

template<class T> vector<T> mult(vector<T> a, vector<T> b) {
	int s = sz(a)+sz(b)-1, n = 1<<size(s);
	vector<T> roots(n); genRoots(roots);
	a.rsz(n), fft(a,roots); 
	b.rsz(n), fft(b,roots);
	F0R(i,n) a[i] *= b[i];
	fft(a,roots,1); return a;
}