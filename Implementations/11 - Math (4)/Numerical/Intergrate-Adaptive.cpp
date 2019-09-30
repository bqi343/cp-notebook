/**
 * Description: https://en.wikipedia.org/wiki/Adaptive_Simpson%27s_method
 * Source: KACTL
 * Verification: ?
 */

// d f(d x) { return x*x+3*x+1; }

d simpson(d (*f)(d), d a, d b) {
	d c = (a+b) / 2;
	return (f(a) + 4*f(c) + f(b)) * (b-a) / 6;
}

d rec(d (*f)(d), d a, d b, d eps, d S) {
	d c = (a+b) / 2;
	d S1 = simpson(f, a, c);
	d S2 = simpson(f, c, b), T = S1 + S2;
	if (abs(T - S) <= 15*eps || b-a < 1e-10)
		return T + (T - S) / 15;
	return rec(f, a, c, eps/2, S1) + rec(f, c, b, eps/2, S2);
}

d quad(d (*f)(d), d a, d b, d eps = 1e-8) {
	return rec(f, a, b, eps, simpson(f, a, b));
}