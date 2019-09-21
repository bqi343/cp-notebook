/**
 * Description: Counts the number of lattice points (x,y) such that 0<x, 0<y, ax+by <= c 
 * Source: Own 
 * Verification: 
 	* https://codeforces.com/contest/1098/problem/E
 	* https://open.kattis.com/problems/probedroids
 */

// sum of a+(a-b)+(a-2b)+...
ll ariSum (ll a, ll b) { 
    if (a <= 0) return 0;
    ll z = a/b; return (z+1)*(2*a-z*b)/2;
}

// counts the number of lattice points (x,y) such that 0<x, 0<y, ax+by <= c 
ll triSum(ll a, ll b, ll c) { 
    if (a+b > c) return 0; 
    if (a > b) swap(a,b);
    ll k = b/a; 
    // if ax+kay <= kac/b then we can divide by a and count 
    // otherwise x > kc/b-ky so we can subtract the latter expression from x and continue
    return triSum(a,b-k*a,c-a*(c*k/b))+ariSum(c*k/b-k,k);
}
ll triSumBrute(ll a, ll b, ll c) { 
    ll ans = 0; for (ll i = c-a; i >= 0; i -= a) ans += i/b;
    return ans;
}

// computes sum_{i=1}^k floor(a*i/b)
ll floorSum(ll a, ll b, ll k) {
    return triSum(a,b,a*(k+1));
}
ll floorSumBrute(ll a, ll b, ll k) {
    ll ans = 0; FOR(i,1,k+1) ans += a*i/b;
    return ans;
}
