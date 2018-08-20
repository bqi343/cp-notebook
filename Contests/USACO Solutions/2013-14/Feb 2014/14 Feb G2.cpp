// #include<iostream>
#include<fstream>
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

ifstream cin ("dec.in");
ofstream cout ("dec.out");

int N,B, dp[1<<20], skill[20][20];
vector<pi> bonus[21];

int main() {
	cin >> N >> B;
	F0R(i,B) {
		int K,P,A; cin >> K >> P >> A;
		bonus[K-1].pb({P,A});
	}
	F0R(i,N) F0R(j,N) cin >> skill[i][j];
	F0R(i,(1<<N)-1) {
		int co = 0;
		F0R(j,N) if (i & (1<<j)) co++;
		F0R(j,N) if ((i & (1<<j)) == 0) {
			int temp = dp[i]+skill[j][co];
			int t = temp;
			for (auto a: bonus[co]) if (temp >= a.f) t += a.s;
			dp[i|(1<<j)] = max(dp[i|(1<<j)],t);
		}
	}
	cout << dp[(1<<N)-1];
}
