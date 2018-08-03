/**
 * Observation: number of operations needed s.t. 
 *                phi(phi(...phi(n)...))=1 
 * is O(log n).
 * Euler's theorem: a^{\phi(p)}\equiv 1 (mod p), gcd(a,p)=1
 * Verification: CF Power Tower
 */

namespace NT {
    // see https://github.com/kth-competitive-programming/kactl/blob/master/content/number-theory/factor.h
    // to factor long longs
    
    vpi fac(int x) {
        vpi pri;
        
        for (int i = 2; i*i <= x; ++i) if (x % i == 0) {
            int t = 0;
            while (x % i == 0) x /= i, t ++;
            pri.pb({i,t});
        }
        
        if (x > 1) pri.pb({x,1});
        return pri;
    }

    int phi(int x) {
        for (auto a: fac(x)) x /= a.f, x *= a.f-1; 
        return x;
    }

    ll inv(ll a, ll b) { // 0 < a < b, gcd(a,b) = 1
        a %= b;
        if (a <= 1) return a;
        ll i = inv(b%a,a);
        ll tmp = -((b/a)*i+((b%a)*i)/a) % b;
        if (tmp < 0) tmp += b;
        return tmp;
    }
 
    pl CRT(pl a, pl b) { // Chinese Remainder Theorem, Verified by Kattis generalchineseremainder
        ll g = __gcd(a.s,b.s), l = a.s*b.s/g;
        if ((b.f-a.f) % g != 0) return {-1,-1};
        ll A = a.s/g, B = b.s/g;
        ll mul = (b.f-a.f)/g*inv(A%B,B) % B;
        return {((mul*a.s+a.f)%l+l)%l,l};
    }
};
