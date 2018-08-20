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

int N, dp[500][500], dp1[500][500];
char grid[500][500];

int main() {
	ifstream cin ("palpath.in");
	ofstream cout ("palpath.out");
	cin >> N;
	if (N == 1) {
		cout << 1;
		return 0;
	}
	F0R(i,N) F0R(j,N) cin >> grid[i][j];
	F0R(i,N-1) {
		F0R(j,i+1) F0R(k,i+1) {
			pi a = {j,i-j}, b = {N-1-k,N-1-i+k};
			if (a.f>b.f || a.s>b.s) continue;
			if (grid[a.f][a.s] == grid[b.f][b.s] && i>0) {
				if (j) {
					if (k) dp1[j][k] = (dp1[j][k]+dp[j-1][k-1]) % MOD;
					dp1[j][k] = (dp1[j][k]+dp[j-1][k]) % MOD;
				}
				if (k) dp1[j][k] = (dp1[j][k]+dp[j][k-1]) % MOD;
				dp1[j][k] = (dp1[j][k]+dp[j][k]) % MOD;
			} else if (grid[a.f][a.s] == grid[b.f][b.s] && i == 0) dp1[j][k] = 1;
		}
		F0R(j,i+1) F0R(k,i+1) {
			dp[j][k] = dp1[j][k];
			dp1[j][k] = 0;
		}
	}
	int ans = 0;
	F0R(i,N) {
		ans = (ans+dp[i][N-1-i]) % MOD;
		if (N-2-i >= 0) ans = (ans+dp[i][N-1-i-1]) % MOD;
		if (i) {
			ans = (ans+dp[i-1][N-1-i]) % MOD;
			if (N-2-i >= 0) ans = (ans+dp[i-1][N-1-i-1]) % MOD;
		}
	}
	cout << ans;
}
