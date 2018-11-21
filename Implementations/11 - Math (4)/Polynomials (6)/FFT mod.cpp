/*
Description: Allows multiplication of polynomials in general moduli. 
Verification: http://codeforces.com/contest/960/submission/37085144
*/

using namespace FFT;

vl conv(vl a, vl b, ll mod) { // 1.2s when sz(a)=sz(b)=1<<19
    int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
    
    vcd v1(n), v2(n), r1(n), r2(n);
    F0R(i,sz(a)) v1[i] = cd(a[i] >> 15, a[i] & 32767);
    F0R(i,sz(b)) v2[i] = cd(b[i] >> 15, b[i] & 32767);
    fft(v1), fft(v2);
    
    F0R(i,n) {
        int j = (i ? (n - i) : i);
        cd ans1 = (v1[i] + conj(v1[j])) * cd(0.5, 0);
        cd ans2 = (v1[i] - conj(v1[j])) * cd(0, -0.5);
        cd ans3 = (v2[i] + conj(v2[j])) * cd(0.5, 0);
        cd ans4 = (v2[i] - conj(v2[j])) * cd(0, -0.5);
        r1[i] = (ans1 * ans3) + (ans1 * ans4) * cd(0, 1);
        r2[i] = (ans2 * ans3) + (ans2 * ans4) * cd(0, 1);
    }
    fft_rev(r1), fft_rev(r2);
    
    vl ret(n);
    F0R(i,n) {
        ll av = (ll)round(r1[i].real());
        ll bv = (ll)round(r1[i].imag()) + (ll)round(r2[i].real());
        ll cv = (ll)round(r2[i].imag());
        av %= mod, bv %= mod, cv %= mod;
        ret[i] = (av << 30) + (bv << 15) + cv;
        ret[i] = (ret[i]%mod+mod)%mod;
    }
    ret.resz(s);
    return ret;
}