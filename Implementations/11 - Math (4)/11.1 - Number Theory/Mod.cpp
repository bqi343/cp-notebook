/*
* Description: Basic operations with modular arithmetic
*/

ll po (ll b, ll p) { return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD; }
ll inv (ll b) { return po(b,MOD-2); }

int ad(int a, int b) { return (a+b)%MOD; }
int sub(int a, int b) { return (a-b+MOD)%MOD; }
int mul(int a, int b) { return (ll)a*b%MOD; }

pi operator+(const pi& l, const pi& r) { return {ad(l.f,r.f),ad(l.s,r.s)}; }
pi operator-(const pi& l, const pi& r) { return {sub(l.f,r.f),sub(l.s,r.s)}; }
pi operator*(const pi& l, const pi& r) { return {mul(l.f,r.f),mul(l.s,r.s)}; }
pi operator*(const int& l, const pi& r) { return {mul(l,r.f),mul(l,r.s)}; }
pi operator*(const pi& l, const int& r) { return r*l; }

pi operator+=(pi& l, const pi& r) { return l = l+r; }
pi operator-=(pi& l, const pi& r) { return l = l-r; }
pi operator*=(pi& l, const int& r) { return l = l*r; }