/**
* Description:
* Source: KACTL, https://pastebin.com/3Tnj5mRu
* Verification: SPOJ polymul, CSA manhattan
*/

typedef complex<double> cd;

namespace FFT {
    int get(int s) { return s > 1 ? 32 - __builtin_clz(s - 1) : 0; }

    void fft(vcd& a) { 
        int N = sz(a), j = 0;
        
        FOR(i,1,N) {
            int k;
            for (k = N >> 1; j >= k; k >>= 1) j -= k;
            j += k; if (i < j) swap(a[i],a[j]);
        }
        
        vl roots(N);
        roots[0] = 1, roots[1] = po(root,(MOD-1)/N);
        FOR(i,2,N) roots[i] = mul(roots[i-1],roots[1]);
        
        for (int i = 2; i <= N; i *= 2) {
            int i2 = i/2;
            for (j = 0; j < N; j += i) {
                for (int k = 0; k < i2; k++) {
                    auto z = mul(a[i2+j+k],roots[N/i*k]); 
                    a[i2+j+k] = sub(a[j+k],z); AD(a[j+k],z);
                }
            }
        }
    } 
    
    void fft_rev(vcd& a) {
        fft(a); trav(x,a) x /= sz(a);
        reverse(beg(a)+1, en(a));
    }
    
    template<class T> T brute(const T& a, const T& b) {
        T c(sz(a)+sz(b)-1);
        F0R(i,sz(a)) F0R(j,sz(b)) c[i+j] += a[i]*b[j];
        return c;
    }
    
    vcd conv(vcd a, vcd b) {
        int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
        if (s <= 0) return {};
        if (s <= 200) return brute(a,b);
        a.resz(n), fft(a); b.resz(n), fft(b);
        F0R(i,n) a[i] *= b[i];
        fft_rev(a); a.resz(s); return a;
    }
    
    vl conv(const vl& a, const vl& b) { 
    	// 0.7s for sz(a)=sz(b)=1<<18
        vcd X = conv(vcd(all(a)),vcd(all(b)));
        vl x(sz(X)); F0R(i,sz(X)) x[i] = round(X[i].real());
        return x;
    }
}

using namespace FFT;