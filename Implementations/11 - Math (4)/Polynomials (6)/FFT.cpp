/**
* Sources: KACTL, https://pastebin.com/3Tnj5mRu
* Verification: SPOJ polymul, CSA manhattan
*/

typedef vector<cd> vcd;

int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}

namespace FFT {
    vcd fft(vcd& a) { 
        int n = a.size(), x = get(n); 
        vcd res, RES(n), roots(n);
        F0R(i,n) roots[i] = cd(cos(2*M_PIl*i/n),sin(2*M_PIl*i/n)); 
        
        res = a;
        FOR(i,1,x+1) {
            int inc = n>>i;
            F0R(j,inc) for (int k = 0; k < n; k += inc)  {
                int t = 2*k%n+j;
                RES[k+j] = res[t]+roots[k]*res[t+inc];
            }
            swap(res,RES);
        }
        
        return res;
    }
    
    vcd fft_rev(vcd& a) {
        vcd res = fft(a);
        F0R(i,sz(res)) res[i] /= a.size();
        reverse(res.begin() + 1, res.end());
        return res;
    }
    
    vcd brute(vcd& a, vcd& b) {
        vcd c(sz(a)+sz(b)-1);
        F0R(i,sz(a)) F0R(j,sz(b)) c[i+j] += a[i]*b[j];
        return c;
    }
    
    vcd conv(vcd a, vcd b) {
        int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
        if (s <= 0) return {};
        if (s <= 200) return brute(a,b);
        
        a.resize(n); a = fft(a);
        b.resize(n); b = fft(b);
        
        F0R(i,n) a[i] *= b[i];
        a = fft_rev(a);
        
        a.resize(s);
        return a;
    }
    
    vl convll(vl a, vl b) {
        vcd A(sz(a)); F0R(i,sz(a)) A[i] = a[i];
        vcd B(sz(b)); F0R(i,sz(b)) B[i] = b[i];
        vcd X = conv(A,B);
        vl x(sz(X)); F0R(i,sz(X)) x[i] = round(X[i].real());
        return x;
    }
}

int main() {
    int T; cin >> T;
    F0R(i,T) {
        int N; cin >> N;
        vl a(N+1), b(N+1);
        F0R(j,N+1) cin >> a[N-j];
        F0R(j,N+1) cin >> b[N-j];
        vl x = FFT::convll(a,b);
        F0Rd(j,sz(x)) cout << x[j] << " ";
        cout << "\n";
    }
}
