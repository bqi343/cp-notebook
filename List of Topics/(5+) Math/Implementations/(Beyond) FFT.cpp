// inspired by
// https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FFT.h
// https://pastebin.com/3Tnj5mRu

typedef complex<double> cd;
typedef vector<cd> vcd;

int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}

vcd fft(vcd& a) { 
    int n = a.size(), x = get(n); 
    vcd res, RES(n), roots(n);
    F0R(i,n) roots[i] = cd(cos(2*M_PI*i/n),sin(2*M_PI*i/n)); 
    
    res = a;
    FOR(i,1,x+1) {
        int inc = n>>i;
        F0R(j,inc) for (int k = 0; k < n; k += inc)  // 1<<i numbers
            RES[k+j] = res[2*k%n+j]+roots[k]*res[2*k%n+j+inc];
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

vcd conv(vcd a, vcd b) {
    int s = sz(a)+sz(b)-1, L = get(s), n = 1<<L;
    if (s <= 0) return {};
    
    a.resize(n); a = fft(a);
    b.resize(n); b = fft(b);
    
    F0R(i,n) a[i] *= b[i];
    a = fft_rev(a);
    
    a.resize(s);
    return a;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    vcd x = conv({1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8});
    for (auto a: x) cout << a << "\n";
}