/**
 * Description: Multiply small polys directly, otherwise use FFT.
 * Source: KACTL, https://cp-algorithms.com/algebra/fft.html
 */

#include "Poly.h"
#include "FFT.h"

bool small(const poly& a, const poly& b) { // multiply directly
	return (ll)sz(a)*sz(b) <= 10000; } 
// vmi smart(const vmi& a, const vmi& b) { return mul(a,b); }
// vl smart(const vl& a, const vl& b) {
// 	auto X = mul(vcd(all(a)),vcd(all(b)));
// 	vl x(sz(X)); F0R(i,sz(X)) x[i] = round(X[i].real());
// 	return x; }
poly conv(const poly& a, const poly& b) {
	return small(a,b) ? a*b : mul(a,b); } 