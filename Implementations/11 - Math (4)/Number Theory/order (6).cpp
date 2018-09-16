
/** Notes: 
* number of operations needed s.t. 
*                phi(phi(...phi(n)...))=1 
* is O(log n).
* Euler's theorem: a^{\phi(p)}\equiv 1 (mod p), gcd(a,p)=1
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