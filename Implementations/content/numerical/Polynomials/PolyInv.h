/**
 * Description: computes $A^{-1}$ such that $AA^{-1}\equiv 1\pmod{x^n}$.
 	* Newton's method: If you want $F(x)=0$ and $F(Q_k)\equiv 0\pmod{x^a}$
 	* then $Q_{k+1}=Q_k-\frac{F(Q_k)}{F'(Q_k)}\pmod{x^{2a}}$ satisfies
 	* $F(Q_{k+1})\equiv 0 \pmod{x^{2a}}$. Application: if $f(n),g(n)$ are the
 	* \#s of forests and trees on $n$ nodes then 
 	* $\sum_{n=0}^{\infty}f(n)x^n=\exp\left(\sum_{n=1}^{\infty}\frac{g(n)}{n!}\right)$.
 * Time: O(N\log N)
 * Source: CF
 	* http://people.csail.mit.edu/madhu/ST12/scribe/lect06.pdf
 	* https://cp-algorithms.com/algebra/polynomial.html
 	* maroonrk's submissions ^_^
 	* if you need faster exp for some reason, see https://old.yosupo.jp/submission/36732 ...
 * Usage: vmi v={1,5,2,3,4}; ps(exp(2*log(v,9),9)); // squares v
 * Verification: https://codeforces.com/contest/438/problem/E
 	* https://codeforces.com/gym/102028/submission/77687049
 	* https://loj.ac/problem/6703 (MultipointEval)
 */

#include "FFT.h"
#include "Poly.h"

/// WARNING: lots of sketchy optimizations to improve constant factors of calls to FFT ...
/// there are much simpler versions of functions below, but they are slower ...

void double_inverse_given(poly& A_inv, poly a, 
		const poly& a_inv) {
	int N = sz(A_inv);
	F0R(i,2*N) a[i] *= a_inv[i];
	fft(a,1); F0R(i,N) a[i] = 0; 
	/// now a represents 1+stuff_{N..3*N-2}, we only care about stuff_{N..2*N-1} 
	/// so we zero out the rest
	fft(a); F0R(i,2*N) a[i] *= a_inv[i];
	fft(a,1); FOR(i,N,2*N) A_inv.pb(-a[i]);
}

void double_inverse(const poly& A, poly& A_inv) { 
	/// given first 2*N terms of A and N terms of A_inv, extend A_inv
	/// add terms N...2*N-1 of -A_inv^2A to A_inv
	int N = sz(A_inv);
	poly f = RSZ(A,2*N); fft(f); // first 2N terms of A
	poly g = RSZ(A_inv,2*N); fft(g);
	double_inverse_given(A_inv,f,g);
}

// A_inv such that A*A_inv = 1
poly inv(const poly& A, int NEED_N) { assert(A[0] != 0);
	// F(Q)=1/Q
	// Q-F(Q)/F'(Q)=Q-(1/Q-A)/(-Q^{-2})
	// =2Q-Q^2A=Q+Q(1-QA)
	poly A_inv{1/A[0]};
	while (sz(A_inv) < NEED_N) double_inverse(A,A_inv);
	return RSZ(A_inv,NEED_N);
}

// e^{result}=A
poly log(poly A, int N) { assert(A[0] == 1); 
	// ln A = integral(A'/A)
	return integ(RSZ(mul(dif(A),inv(A,N-1)),N-1)); }

// A_sqrt^2=A
poly sqrt(const poly& A, int NEED_N) { assert(A[0] == 1); 
	// F(Q)=Q^2-A
	// Q-F(Q)/F'(Q)=Q-(Q^2-A)/(2Q)
	// =1/2(Q+A/Q)
	const T i2 = T(1)/T(2);
	poly A_sqrt{1}, A_sqrt_inv{1},a_sqrt{1};
	auto value_at = [&](int i) -> T { return i<sz(A)?A[i]:0; };
	for (int N = 1; N < NEED_N; N *= 2) {
		F0R(i,N) a_sqrt[i] *= a_sqrt[i]; // z is transform of Q^2
		fft(a_sqrt,1); poly delta(2*N); // set delta = Q^2-A
		F0R(i,N) delta[N+i] = a_sqrt[i]-value_at(i)-value_at(N+i);
		fft(delta); 
		poly a_sqrt_inv = RSZ(A_sqrt_inv,2*N);
		fft(a_sqrt_inv); F0R(i,2*N) delta[i] *= a_sqrt_inv[i];
		fft(delta,1); FOR(i,N,2*N) A_sqrt.pb(-i2*delta[i]);
		// get terms of (Q^2-A)/2Q
		if (2*N >= NEED_N) break;
		a_sqrt = A_sqrt; fft(a_sqrt);
		double_inverse_given(A_sqrt_inv,a_sqrt,a_sqrt_inv);
	}
	return RSZ(A_sqrt,NEED_N);
}

// e^A
poly exp(const poly& A, int NEED_N) { assert(A[0] == 0);
	// F(Q)=ln(Q)-A
	// Q-F(Q)/F'(Q)=Q-(ln(Q)-A)/(1/Q)
	// =Q*(1+A-ln(Q))=Q+Q*(A-ln(Q))
	auto value_at = [&](int i) -> T { return i<sz(A)?A[i]:0; };
	auto conv_given = [&](const poly& a, poly b) {
		b.rsz(sz(a)); fft(b); // fft already applied to a
		F0R(i,sz(b)) b[i] *= a[i];
		fft(b,1); return b; };
	poly A_exp{1}, A_inv{1};
	for (int N = 1; N < NEED_N; N *= 2) { // sz(A_exp) = N
		poly a_exp = RSZ(A_exp,2*N); fft(a_exp);
		if (N > 1) {
			poly a_inv_small = RSZ(A_inv,2*N); fft(a_inv_small);
			F0R(i,2*N) a_inv_small[i] *= a_inv_small[i]*a_exp[i];
			fft(a_inv_small,1);
			FOR(i,N/2,N) A_inv.pb(-a_inv_small[i]);
		}
		poly a_inv = RSZ(A_inv,2*N); fft(a_inv);
		poly ln = conv_given(a_inv,dif(A_exp));
		poly a_inv_exp(2*N); 
		F0R(i,2*N) a_inv_exp[i] = a_inv[i]*a_exp[i];

		poly a_dif = RSZ(dif(RSZ(A,N)),2*N); fft(a_dif);
		F0R(i,2*N) a_inv_exp[i] *= a_dif[i];
		fft(a_inv_exp,1); FOR(i,N,2*N) ln[i] -= a_inv_exp[i];
		ln.pop_back(); ln = integ(ln);

		poly A_minus_ln(N); 
		F0R(i,N) A_minus_ln[i] = value_at(i+N)-ln[i+N];
		poly prod = conv_given(a_exp,A_minus_ln); // conv(N,N)
		FOR(i,N,2*N) A_exp.pb(prod[i-N]);
	} 
	return RSZ(A_exp,NEED_N);
}