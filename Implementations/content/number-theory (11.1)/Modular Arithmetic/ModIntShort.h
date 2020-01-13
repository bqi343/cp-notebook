/**
 * Description: modular arithmetic operations 
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 */

typedef int T; 
struct mi {
 	T v; explicit operator T() const { return v; }
	mi(ll _v) : v(_v%MOD) { v += (v<0)*MOD; }
	mi() : mi(0) {}
};
mi operator+(mi a, mi b) { return mi(a.v+b.v); }
mi operator-(mi a, mi b) { return mi(a.v-b.v); }
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }
mi pow(mi a, ll p) {
	mi ans = 1; assert(p >= 0);
	for (; p; p /= 2, a = a*a) if (p&1) ans = ans*a;
	return ans;
}
mi inv(const mi& a) { assert(a.v != 0); return pow(a,MOD-2); }
mi operator/(mi a, mi b) { return a*inv(b); }
/// mi a = MOD+5; ps((int)inv(a));