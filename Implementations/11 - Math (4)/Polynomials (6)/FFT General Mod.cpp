/*
Description: Allows multiplication of polynomials in general moduli. 
Verification: http://codeforces.com/contest/960/submission/37085144
*/

namespace FFT {
    int get(int s) {
        return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
    }
    
    void fft(vcd& a, bool inv){
    	int n = sz(a), j = 0;
    	vcd roots(n/2);
    	FOR(i,1,n) {
    		int bit = (n >> 1);
    		while (j >= bit){
    			j -= bit;
    			bit >>= 1;
    		}
    		j += bit;
    		if(i < j) swap(a[i], a[j]);
    	}

    	ld ang = 2 * M_PIl / n * (inv ? -1 : 1);
    	F0R(i,n/2) roots[i] = cd(cos(ang * i), sin(ang * i));
    
    	for (int i=2; i<=n; i<<=1){
    		int step = n / i;
    		for(int j=0; j<n; j+=i){
    			for(int k=0; k<i/2; k++){
    				cd u = a[j+k], v = a[j+k+i/2] * roots[step * k];
    				a[j+k] = u+v;
    				a[j+k+i/2] = u-v;
    			}
    		}
    	}
    	
    	if (inv) F0R(i,n) a[i] /= n;
    }
    
    vl conv(vl a, vl b, ll mod){
        int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
        
    	vcd v1(n), v2(n), r1(n), r2(n);
    	F0R(i,sz(a)) v1[i] = cd(a[i] >> 15, a[i] & 32767);
    	F0R(i,sz(b)) v2[i] = cd(b[i] >> 15, b[i] & 32767);
    	fft(v1, 0); fft(v2, 0);
    	
    	F0R(i,n) {
    		int j = (i ? (n - i) : i);
    		cd ans1 = (v1[i] + conj(v1[j])) * cd(0.5, 0);
    		cd ans2 = (v1[i] - conj(v1[j])) * cd(0, -0.5);
    		cd ans3 = (v2[i] + conj(v2[j])) * cd(0.5, 0);
    		cd ans4 = (v2[i] - conj(v2[j])) * cd(0, -0.5);
    		r1[i] = (ans1 * ans3) + (ans1 * ans4) * cd(0, 1);
    		r2[i] = (ans2 * ans3) + (ans2 * ans4) * cd(0, 1);
    	}
    	fft(r1, 1); fft(r2, 1);
        vl ret(n);
    	F0R(i,n) {
    		ll av = (ll)round(r1[i].real());
    		ll bv = (ll)round(r1[i].imag()) + (ll)round(r2[i].real());
    		ll cv = (ll)round(r2[i].imag());
    		av %= mod, bv %= mod, cv %= mod;
    		ret[i] = (av << 30) + (bv << 15) + cv;
    		ret[i] %= mod; ret[i] += mod; ret[i] %= mod;
    	}
    	ret.resize(s);
    	return ret;
    }
}