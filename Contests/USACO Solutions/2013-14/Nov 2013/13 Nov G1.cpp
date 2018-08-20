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

const int MOD = 1000000007;
double PI = 4*atan(1);

int cow[3000000], rec[3000000], N, K;

ifstream cin ("empty.in");
ofstream cout ("empty.out");

int main() {
	cin >> N >> K;
	F0R(i,K) {
		ll X,Y,A,B; cin >> X >> Y >> A >> B;
		FOR(j,1,Y+1) {
			int sta = (A*j+B) % N;
			cow[sta] += X;
		}
	}
	int mx = -MOD, cur = 0;
	FORd(i,1,N+1) {
		if (i == N) rec[i-N] = cow[i-N];
		else rec[i] = rec[(i+1) % N]-1+cow[i];
		mx = max(mx,rec[i%N]);
	}
	while (mx > cur) {
		int cur1 = mx, mx1 = mx;
		FORd(i,cur+1,cur1+1) {
			if (i == cur1) rec[i] = cur1+cow[i];
			else rec[i] = rec[i+1]-1+cow[i];
			mx1 += cow[i];
			mx = max(mx,rec[i]);
		}
		cur = cur1;
		mx = max(mx1,mx);
	}
	cout << cur;
}
