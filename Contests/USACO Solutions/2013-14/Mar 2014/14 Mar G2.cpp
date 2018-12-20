// #include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<unordered_map>
#include<cmath>
#include<cstring>
#include<string>
#include<bitset>
#include<algorithm>
#include<vector>
#include<iomanip>

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

double lo = 0, hi = 10000, sum[200001];
int N, num[100001];

bool ok(double mid) { // can you get less than that
	sum[0] = 0;
	FOR(i,1,N+1) sum[i] = sum[i-1]+num[i]-mid;
	FOR(i,N+1,2*N+1) sum[i] = sum[i-1]+num[i-N]-mid;
	double mx = -MOD;
	FORd(i,N+1,2*N-1) { // 2*N-2: N
		mx = max(mx,sum[i-(N-1)]);
		if (mx > sum[i]) return 1;
	}
	return 0;
}

int main() {
	ifstream cin ("sabotage.in");
	ofstream cout ("sabotage.out");
	cin >> N;
	FOR(i,1,N+1) cin >> num[i];
	while (hi-lo > 0.000001) { // lowest possible average
		double mid = (lo+hi)/2;
		if (ok(mid)) hi = mid;
		else lo = mid;
	}
	cout << fixed << setprecision(3) << (lo+hi)/2;
}
