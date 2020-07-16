/**
 * Description: Multiply two polynomials with arbitrary $MOD.$
	* Ensures precision by splitting into halves.
 * Source: KACTL, https://cp-algorithms.com/algebra/fft.html
 * Time: $\sim$0.8s when \texttt{sz(a)=sz(b)=1<<19}
 * Verification: see FFT
 */

#include "FFT.h"

vl mulMod(const vl& a, const vl& b) { 
	if (!min(sz(a),sz(b))) return {};
	int s = sz(a)+sz(b)-1, n = 1<<size(s), cut = sqrt(MOD);
	vcd roots(n); genRoots(roots);
	vcd ax(n), bx(n);
	// ax(x)=a1(x)+i*a0(x)
	F0R(i,sz(a)) ax[i] = cd((int)a[i]/cut, (int)a[i]%cut); 
	// bx(x)=b1(x)+i*b0(x)
	F0R(i,sz(b)) bx[i] = cd((int)b[i]/cut, (int)b[i]%cut); 
	fft(ax,roots), fft(bx,roots);
	vcd v1(n), v0(n);
	F0R(i,n) {
		int j = (i ? (n-i) : i);
		// v1 = a1*(b1+b0*cd(0,1));
		v1[i] = (ax[i]+conj(ax[j]))*cd(0.5,0)*bx[i]; 
		// v0 = a0*(b1+b0*cd(0,1));
		v0[i] = (ax[i]-conj(ax[j]))*cd(0,-0.5)*bx[i]; 
	}
	fft(v1,roots,1), fft(v0,roots,1);
	vl ret(n);
	F0R(i,n) {
		ll V2 = (ll)round(v1[i].real()); // a1*b1
		ll V1 = (ll)round(v1[i].imag())+(ll)round(v0[i].real()); 
		// a0*b1+a1*b0
		ll V0 = (ll)round(v0[i].imag()); // a0*b0
		ret[i] = ((V2%MOD*cut+V1)%MOD*cut+V0)%MOD;
	}
	ret.rsz(s); return ret;
} 