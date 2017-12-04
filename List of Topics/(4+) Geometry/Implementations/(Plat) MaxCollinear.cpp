// https://open.kattis.com/problems/maxcolinear

int n, mx, ans;
map<pair<pii,int>,int> m;
pii p[1000];

pair<pii,int> getline(pii a, pii b) {
    pii z = {b.f-a.f,b.s-a.s};
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

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	while (cin >> n) {
	    if (n == 0) break;
	    solve();
	}
}

// read!
// ll vs. int!
