/**
 * Description: Multiply two polynomials of modular ints. For xor convolution 
 	* ignore \texttt{m}. If product of sizes is at most a certain 
 	* threshold (ex. 10000) then it's faster to multiply directly.
 * Time: O(N\log N)
 * Source: 
 	* KACTL
 	* https://cp-algorithms.com/algebra/fft.html
 	* https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it
 	* maroonrk
 * Verification: 
	* https://judge.yosupo.jp/problem/convolution_mod
	* SPOJ polymul, CSA manhattan, CF Perfect Encoding
	* http://codeforces.com/contest/632/problem/E
 */

#include "ModInt.h"
// const int MOD = 998244353;

template<class T> void fft(vector<T>& A, bool inv = 0) {
	int n = sz(A); assert((T::mod-1)%n == 0); vector<T> B(n);
	for(int b = n/2; b; b /= 2, swap(A,B)) {
		T w = pow(T::rt(),(T::mod-1)/n*b), m = 1;
		for(int i = 0; i < n; i += b*2, m *= w) F0R(j,b) {
			T u = A[i+j], v = A[i+j+b]*m;
			B[i/2+j] = u+v; B[i/2+j+n/2] = u-v;
		}
	}
	if (inv) { reverse(1+all(A)); 
		T z = T(1)/T(n); trav(t,A) t *= z; }
}
template<class T> vector<T> mul(vector<T> A, vector<T> B) { 
	if (!min(sz(A),sz(B))) return {};
	int s = sz(A)+sz(B)-1, n = 1; for (; n < s; n *= 2);
	bool eq = A == B; A.rsz(n), fft(A);
	if (eq) B = A; // squaring A, so remove one FFT
	else B.rsz(n), fft(B);
	F0R(i,n) A[i] *= B[i];
	fft(A,1); A.rsz(s); return A;
}