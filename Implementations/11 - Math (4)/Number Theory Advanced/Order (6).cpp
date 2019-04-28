/**
 * Description: Calculates smallest P such that x^P equiv 1 (mod p)
 * Source: Own
 * Verification: ?
 */

using namespace rpm;
using namespace basicFactor;

ll order(ll x, ll p) {
    if (__gcd(x,p) != 1) return 0;
    ll P = phi(p); auto a = fac(P);
    trav(t,a) while (P % t.f == 0 && mod_pow(x,P/t.f,p) == 1) P /= t.f;
    return P;
}
