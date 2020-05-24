// from dhruv rohatgi
// runs in N^2loglogN?

#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 5001
 
int mod;
int N;
int ch[MAXN][MAXN];	//number of ways to pick k with order from n
bool prime[MAXN];
 
int mult(int a,int b)
{
	return (a*((long long)b))%(mod-1);
}
 
int add(int a,int b)
{
	a += b;
	if(a >= (mod-1)) a -= (mod-1);
	return a;
}
 
void precompute()
{
	for(int n=2;n<MAXN;n++)
		prime[n] = 1;
	for(int n=2;n<MAXN;n++) if(prime[n])
	{
		for(int k=2*n;k<MAXN;k+=n)
			prime[k] = 0;
	}
	for(int n=0;n<=N;n++)
	{
		ch[n][0] = 1;
		for(int k=1;k<=n;k++)
			ch[n][k] = mult(ch[n][k-1], n+1-k);
	}
}
 
int dp[MAXN];	//number of permutations of [n] s.t. each cycle has length nonzero modulo k
 
int solve(int k)
{
	if(k>N) return ch[N][N];
	dp[0] = 1;
	int tot = 0;
	for(int n=1;n<=N;n++)
	{
		tot = (tot*((long long)(n-1)) + dp[n-1])%(mod-1);
		dp[n] = tot;
		for(int L=k;L<=n;L+=k)
			dp[n] = (dp[n]+ ((mod-1) - ch[n-1][L-1])*((long long)dp[n-L]))%(mod-1);
//		cout << ch[n-1][k-1] << '\n';
//		cout << n << ": " << tot <<  ' ' << dp[n][k] << '\n';
	}
	return dp[N];
}
 
int pw(int a,int e)
{
	if(e==0) return 1;
	int b = pw(a,e/2);
	b = (b*((long long)b))%mod;
	if(e&1) b = (b*((long long)a))%mod;
	return b;
}
 
int ways[MAXN];
 
int main()
{
	cin >> N >> mod;
	precompute();
	int ans = 1;
	for(int p=2;p<=N;p++) if(prime[p])
	{
		for(long long k=p;k<=N*p;k*=p)
		{
			int req = solve(k);
			if (k <= N) ways[k] = req;
			if(k>p) req = (req + (mod - 1) - ways[k/p])%(mod-1);
			ans = (ans * ((long long)pw(k/p, req)))%mod;
		}
	}
	cout << ans << '\n';
}