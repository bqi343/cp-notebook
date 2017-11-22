// https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FFT.h

typedef valarray<complex<double> > carray;

void fft(carray& x, carray& roots) {
	int N = sz(x);
	if (N <= 1) return;
	carray even = x[slice(0, N/2, 2)];
	carray odd = x[slice(1, N/2, 2)];
	carray rs = roots[slice(0, N/2, 2)];
	fft(even, rs); fft(odd, rs);
	F0R(k,N/2) {
		auto t = roots[k] * odd[k];
		x[k    ] = even[k] + t;
		x[k+N/2] = even[k] - t;
	}
}

typedef vector<double> vd;

vd conv(const vd& a, const vd& b) {
	int s = sz(a) + sz(b) - 1, L = 32-__builtin_clz(s), n = 1<<L;
	if (s <= 0) return {};
	carray av(n), bv(n), roots(n);
	F0R(i,n) roots[i] = polar(1.0, -2 * M_PI * i / n);
	copy(a.begin(),a.end(),begin(av)); fft(av, roots);
	copy(b.begin(),b.end(),begin(bv)); fft(bv, roots);
	roots = roots.apply(conj);
	carray cv = av * bv; fft(cv, roots);
	vd c(s); F0R(i,s) c[i] = cv[i].real() / n;
	return c;
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	vd a = {1,1}, b = {1,1};
	vd c = conv(a,b);
	for (auto d: c) cout << d << " ";
}

// read!
// ll vs. int!
