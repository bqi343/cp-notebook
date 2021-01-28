/**
 * Description: Compute the maximum number of points which lie on the same line in O(n^2logn)
 * Source: own
 * Verification: https://open.kattis.com/problems/maxcolinear
 */

pair<pi,int> getline(pi a, pi b) {
	pi z = {b.f-a.f,b.s-a.s};
	swap(z.f,z.s); z.f *= -1;
	int g = __gcd(z.f,z.s); z.f /= g, z.s /= g;
	ckmin(z,{-z.f,-z.s});
	return {z,z.f*a.f+z.s*a.s};
}

int solve(vpi p) {
	int n = sz(p);
	map<pair<pi,int>,int> m;
	F0R(i,n) FOR(j,i+1,n) m[getline(p[i],p[j])] ++;

	int mx = 0; each(a,m) ckmax(mx,a.s);
	int ans = 0; FOR(i,1,n+1) if (i*(i-1)/2 <= mx) ans = i;
	return ans;
}
