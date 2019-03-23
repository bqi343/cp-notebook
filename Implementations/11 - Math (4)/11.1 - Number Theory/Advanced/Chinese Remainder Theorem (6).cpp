/**
 * Description: Chinese Remainder Theorem
 * Source: Own
 * Verification: Kattis generalchineseremainder
 * Dependency: Modular Int
 */


pl solve(pl a, pl b) {
    auto g = __gcd(a.s,b.s), l = a.s*b.s/g;
    if ((b.f-a.f) % g != 0) return {-1,-1};
    auto A = a.s/g, B = b.s/g;
    auto mul = (b.f-a.f)/g*invGeneral(A,B) % B;
    return {((mul*a.s+a.f)%l+l)%l,l};
}
