/**
 * Description: Modular arithmetic operations. To make faster, 
 	* change add and subtract so that they don't require \texttt{\%}.
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 */

struct mi {
 	int v; explicit operator int() const { return v; } 
	mi() { v = 0; }
	mi(ll _v):v(_v%MOD) { v += (v<0)*MOD; }
};
mi& operator+=(mi& a, mi b) { 
	if ((a.v += b.v) >= MOD) a.v -= MOD; 
	return a; }
mi operator+(mi a, mi b) { return a += b; }
mi& operator-=(mi& a, mi b) { 
	if ((a.v -= b.v) < 0) a.v += MOD; 
	return a; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }
mi pow(mi a, ll p) {
	mi ans = 1; assert(p >= 0);
	for (;p;p/=2,a=a*a) if (p&1) ans = ans*a;
	return ans; }
mi inv(const mi& a) { assert(a.v != 0); return pow(a,MOD-2); }
mi operator/(mi a, mi b) { return a*inv(b); }
/// mi a = MOD+5; ps((int)inv(a));