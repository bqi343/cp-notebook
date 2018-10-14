/** 
* Description: Calculates smallest P such that x^P equiv 1 (mod p)
* Source: Own
* Verification: ?
*/

using namespace RPM;
using namespace factor1;

ll order(ll x, ll p) {
    if (__gcd(x,p) != 1) return 0;
    ll P = phi(p);
    auto a = fac(P);
    
    for (auto t: a) while (P % t.f == 0 && mod_pow(x,P/t.f,p) == 1) P /= t.f;
    return P;
}