#include <fstream>
#include<vector>
// #include<iostream>
#include<algorithm>
#include<set>
#include<map>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef set<int> si;
typedef map<int,int> mii;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = b-1; i >= a; i--)
#define F0Rd(i,a) for (int i = a-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
 
ll MOD = 1000000009;

ifstream cin ("team.in");
ofstream cout ("team.out");

int N,M,K;

ll dp[1001][1001][11];
vector<ll> fj, fp;

void input() {
    cin >> N >> M >> K;
    fj.resize(N), fp.resize(M);
    F0R(i,N) cin >> fj[i];
    F0R(i,M) cin >> fp[i];
    sort(fj.begin(),fj.end());
    sort(fp.begin(),fp.end());
}

void dynamic() {
    F0R(i,N+1) F0R(j,M+1) dp[i][j][0] = 1;
    FOR(i,1,N+1) FOR(j,1,M+1) FOR(k,1,K+1) {
        dp[i][j][k] = (dp[i][j-1][k]+dp[i-1][j][k]-dp[i-1][j-1][k]) % MOD;
        while (dp[i][j][k]<0) dp[i][j][k] += MOD;
        if (fj[i-1] > fp[j-1]) dp[i][j][k] = (dp[i][j][k] + dp[i-1][j-1][k-1]) % MOD;
    }
}

int main() {
    input();
    dynamic();
    cout << dp[N][M][K];
}
