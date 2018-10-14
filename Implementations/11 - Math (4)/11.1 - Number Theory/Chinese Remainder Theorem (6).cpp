/**
* Description: Chinese Remainder Theorem
* Source: Own
* Verification: Kattis generalchineseremainder
*/

using namespace modOp;

pl solve(pl a, pl b) {
    ll g = __gcd(a.s,b.s), l = a.s*b.s/g;
    if ((b.f-a.f) % g != 0) return {-1,-1};
    ll A = a.s/g, B = b.s/g;
    ll mul = (b.f-a.f)/g*invGeneral(A%B,B) % B;
    return {((mul*a.s+a.f)%l+l)%l,l};
}