/**
* Description: Basic operations with modular arithmetic
*/

ll po (ll b, ll p) { return !p?1:po(b*b%MOD,p/2)*(p&1?b:1)%MOD; }
ll inv (ll b) { return po(b,MOD-2); }

int ad(int a, int b) { return (a+b)%MOD; }
int sub(int a, int b) { return (a-b+MOD)%MOD; }
int mul(int a, int b) { return (ll)a*b%MOD; }

int AD(int& a, int b) { return a = ad(a,b); }
int SUB(int& a, int b) { return a = sub(a,b); }
int MUL(int& a, int b) { return a = mul(a,b); }