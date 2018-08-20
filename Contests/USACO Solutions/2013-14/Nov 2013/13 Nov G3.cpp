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

int ans = -1, dp[1<<16],K,N;
vi x, val, cum;

int fill(int sta, int sz) {
	int lo = sta, hi = N;
	while (lo < hi) { // highest such that less than or equal
		int mid = (lo+hi+1)/2;
		if (cum[mid]-cum[sta] <= sz) lo = mid;
		else hi = mid-1;
	}
	return lo;
}

int main() {
	ifstream cin ("nochange.in");
	ofstream cout ("nochange.out");
	cin >> K >> N; x.resize(K), val.resize(N+1), cum.resize(N+1);
	F0R(i,K) cin >> x[i];
	FOR(i,1,N+1) {
		cin >> val[i];
		cum[i] = cum[i-1]+val[i];
	}
	FOR(i,1,1<<K) {
		F0R(j,K) if (i & (1<<j)) dp[i] = max(dp[i],fill(dp[i^(1<<j)],x[j]));
		if (dp[i] == N) {
			int sum = 0;
			F0R(j,K) if ((i & (1<<j)) == 0) sum += x[j];
			ans = max(ans,sum);
		}
	}
	cout << ans;
}
