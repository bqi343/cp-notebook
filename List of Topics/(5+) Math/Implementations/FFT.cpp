// https://pastebin.com/3Tnj5mRu
// also see NTT

typedef complex<double> cd;
typedef vector<cd> vcd;

int get(int s) {
    return s > 1 ? 32 - __builtin_clz(s - 1) : 0;
}

vcd fft(const vcd &as) {
    int n = as.size(), k = get(n);
    
    vi rev(n);
    rev[0] = 0;
    int high1 = -1;
    FOR(i,1,n) {
        if ((i & (i - 1)) == 0) high1++;
        rev[i] = rev[i ^ (1 << high1)]; 
        rev[i] |= (1 << (k - high1 - 1)); 
    }
    
    vcd roots(n);
    F0R(i,n) {
        double alpha = 2 * M_PI * i / n;
        roots[i] = cd(cos(alpha), sin(alpha));
    }
    
    vcd cur(n);
    F0R(i,n) cur[i] = as[rev[i]];
    
    for (int len = 1; len < n; len <<= 1) {
        vcd ncur(n);
        int rstep = roots.size() / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            F0R(i,len) {
                cd val = roots[i * rstep] * cur[p1 + len];
                ncur[pdest] = cur[p1] + val;
                ncur[pdest + len] = cur[p1] - val;
                pdest++, p1++;
            }
            pdest += len;
        }
        cur.swap(ncur);
    }
    return cur;
}
 
vcd fft_rev(vcd &as) {
    vcd res = fft(as);
    F0R(i,sz(res)) res[i] /= as.size();
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

vcd square(vcd a) {
    int s = 2*sz(a)-1, L = get(s), n = 1<<L;
	if (s <= 0) return {};
	
	a.resize(n); a = fft(a);
	F0R(i,n) a[i] *= a[i];
	a = fft_rev(a);
	
	a.resize(s);
	return a;
}