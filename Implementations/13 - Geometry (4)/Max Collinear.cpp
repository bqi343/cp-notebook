/**
* Description: Compute the maximum number of points which lie on the same line in O(n^2logn)
* Source: own
* Verification: https://open.kattis.com/problems/maxcolinear
*/

int n, mx, ans;
map<pair<pi,int>,int> m;
pi p[1000];

pair<pi,int> getline(pi a, pi b) {
    pi z = {b.f-a.f,b.s-a.s};
    swap(z.f,z.s); z.f *= -1;
    int g = __gcd(z.f,z.s); z.f /= g, z.s /= g;
    if (z.f < 0 || (z.f == 0 && z.s < 0)) z.f *= -1, z.s *= -1;
    return {z,z.f*a.f+z.s*a.s};
}

void solve() {
    mx = ans = 0; m.clear();
    F0R(i,n) cin >> p[i].f >> p[i].s;
    F0R(i,n) FOR(j,i+1,n) m[getline(p[i],p[j])] ++;
    
    for (auto a: m) mx = max(mx,a.s);
    FOR(i,1,n+1) if (i*(i-1)/2 <= mx) ans = i;
    cout << ans << "\n";
}
