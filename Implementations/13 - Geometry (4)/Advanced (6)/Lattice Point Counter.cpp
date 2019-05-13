/**
 * Description: Counts the number of lattice points (x,y) such that 0<x, 0<y, ax+by <= c 
 * Source: Own 
 * Verification: https://codeforces.com/contest/1098/problem/E
 */

ll getSum (ll a, ll b) { // sum of a+(a-b)+(a-2b)+...
    if (a <= 0) return 0;
    ll z = a/b; return (z+1)*(2*a-z*b)/2;
}

ll getTri(ll c, ll a, ll b) { 
    if (a+b > c) return 0; if (a > b) swap(a,b);
    ll k = b/a; 
    // if ax+kay <= kac/b then we can divide by a and count 
    // otherwise x > kc/b-ky so we can subtract the latter expression from x and continue
    return getTri(c-a*(c*k/b),a,b-k*a)+getSum(c*k/b-k,k);
}

ll brute(ll c, ll a, ll b) { // should equal above
    ll ans = 0; for (ll i = c-a; i >= 0; i -= a) ans += i/b;
    return ans;
}