/*#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>*/
#include <bits/stdc++.h>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
double PI = 4*atan(1);

int N, ans = 0;
map<pair<pi,int>,int> c1, c2;
vector<pi> cow;

pair<pi,int> perp (pi a, pi b) {
    pi slope = {b.f-a.f,b.s-a.s};
    int g = __gcd(slope.f,slope.s);
    slope.f /= g, slope.s /= g;
    swap(slope.f,slope.s);
    slope.s *= -1;
    if (slope.f < 0 || (slope.f == 0 && slope.s < 0)) slope.f *= -1, slope.s *= -1;
    pair<double,double> x = {(a.f+b.f)/2.0,(a.s+b.s)/2.0};
    return {slope,slope.s*x.f*2-slope.f*x.s*2};
}

pair<pi,int> col (pi a, pi b) {
    pi slope = {b.f-a.f,b.s-a.s};
    int g = __gcd(slope.f,slope.s);
    slope.f /= g, slope.s /= g;
    if (slope.f < 0 || (slope.f == 0 && slope.s < 0)) slope.f *= -1, slope.s *= -1;
    return {slope,slope.s*a.f*2-slope.f*a.s*2};
}

bool on(pair<pi,int> x, pi y) {
    int tmp = 2*(x.f.s*y.f-x.f.f*y.s);
    if (tmp == x.s) return 1;
    return 0;
}

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> N; cow.resize(N);
	F0R(i,N) cin >> cow[i].f >> cow[i].s;
	F0R(i,N) FOR(j,i+1,N) {
	    c1[perp(cow[i],cow[j])] ++;
	    c2[col(cow[i],cow[j])] ++;
	}
	
	for (auto& a: c2) if (a.s == N*(N-1)/2) ans++;
	for (auto& a: c1) {
	    int x = N-2*a.s;
	    if (x == 0 || (x >= 2 && c2.find(a.f) != c2.end() && c2[a.f] == x*(x-1)/2)) ans++;
	}
	for (auto& a: c1) if (2*a.s+1 == N) { // do stuff
	    int co = 0;
	    F0R(i,N) if (on(a.f,cow[i])) {
	        co ++;
	        break;
	    }
	    if (co == 1) ans ++;
	}
	cout << ans;
}
