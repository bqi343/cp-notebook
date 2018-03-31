// #include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;
//using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<ll,ll> pi;
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

ifstream cin ("curling.in");
ofstream cout ("curling.out");

vector<pi> lo, hi, a, b;
int N, a1, b1, cur1, cur2;

ll cross(pi O, pi A, pi B) {
	return (A.f - O.f) * (B.s - O.s) - (A.s - O.s) * (B.f - O.f);
}

void convex_hull(vector<pi> P) { // correct
	int n = P.size(), k = 0;
	cur1 = 0, cur2 = 0;
	vector<pi> H(2*n);
	//lower
	F0R(i,n) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	int k1 = k;
	
	// upper
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	lo.clear(); hi.clear();;
	F0R(i,k1) lo.pb(H[i]);
	FOR(i,k1-1,k) hi.pb(H[i]);
	reverse(hi.begin(),hi.end());
}

bool above(pi z, pi a, pi b) {
	if (a.f == b.f) {
		if (z.s >= min(a.s,b.s)) return 1;
		return 0;
	}
	if ((z.f-a.f)*b.s+(b.f-z.f)*a.s <= (b.f-a.f)*z.s) return 1;
	return 0;
}

bool below(pi z, pi a, pi b) {
	if (a.f == b.f) {
		if (z.s <= max(a.s,b.s)) return 1;
		return 0;
	}
	if ((z.f-a.f)*b.s+(b.f-z.f)*a.s >= (b.f-a.f)*z.s) return 1;
	return 0;
}

bool in (pi z) {
	if (z.f < lo[0].f || z.f > lo[lo.size()-1].f) return 0;
	while (cur1 < lo.size()-2 && lo[cur1+1].f <= z.f) cur1++;
	if (!above(z,lo[cur1],lo[cur1+1])) return 0;
	while (cur2 < hi.size()-2 && hi[cur2+1].f <= z.f) cur2++;
	if (!below(z,hi[cur2],hi[cur2+1])) return 0;
	return 1;
}

int main() {
	cin >> N; a.resize(N), b.resize(N);
	F0R(i,N) cin >> a[i].f >> a[i].s;
	F0R(i,N) cin >> b[i].f >> b[i].s;
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	
	convex_hull(a);
	for (pi z: b) if (in(z)) a1 ++;
	convex_hull(b);
	for (pi z: a) if (in(z)) b1 ++;
	
	cout << a1 << " " << b1; // 4114 4120
}
