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

ifstream cin ("subrev.in");
ofstream cout ("subrev.out");

vi a;
int best[51][51][51][51], ans[51][51];
bool done[51][51];

void dfs(int low, int high) {
	if (low>high) return;
	if (done[low][high]) return;
	
	done[low][high] = 1;
	dfs(low+1,high);
	dfs(low,high-1);
	dfs(low+1,high-1);
	
	FOR(i,1,51) FOR(j,i,51) {
		if (low<high) {
			best[low][high][i][j] = max(best[low][high][i][j],best[low+1][high][i][j]);
			best[low][high][i][j] = max(best[low][high][i][j],best[low][high-1][i][j]);
		}
		if (low+1<high)
			best[low][high][i][j] = max(best[low][high][i][j],best[low+1][high-1][i][j]);
	}
	
	int m1 = min(a[low],a[high]), m2 = max(a[low],a[high]);
	
	best[low][high][m1][m1] = max(best[low][high][m1][m1],1);
	best[low][high][m2][m2] = max(best[low][high][m2][m2],1);
	
	if (low != high) best[low][high][m1][m2] = max(best[low][high][m1][m2],2);
	
	if (low+1<high) 
		FOR(i,m1,m2+1) FOR(j,i,m2+1)
			best[low][high][m1][m2] = max(best[low+1][high-1][i][j]+2,best[low][high][m1][m2]);
	
	if (low<high) 
		FOR(i,a[low],51) FOR(j,i,51) 
			if (best[low+1][high][i][j] != 0)
				best[low][high][a[low]][j] = max(best[low][high][a[low]][j], 1+best[low+1][high][i][j]);		
	
	
	if (low<high) 
		FOR(i,1,a[high]+1) FOR(j,i,a[high]+1) 
			if (best[low][high-1][i][j] != 0)
				best[low][high][i][a[high]] = max(best[low][high][i][a[high]], 1+best[low][high-1][i][j]);
	
	if (low+1<high)
		FOR(i,a[high],51) FOR(j,i,51) 
			if (best[low+1][high-1][i][j] != 0)
				best[low][high][a[high]][j] = max(best[low][high][a[high]][j], 1+best[low+1][high-1][i][j]);		
	
	if (low+1<high) 
		FOR(i,1,a[low]+1) FOR(j,i,a[low]+1) 
			if (best[low+1][high-1][i][j] != 0)
				best[low][high][i][a[low]] = max(best[low][high][i][a[low]], 1+best[low+1][high-1][i][j]);
	
	FOR(i,1,51) FOR(j,i,51) ans[low][high] = max(ans[low][high],best[low][high][i][j]);
	// cout << low << " " << high << " " << ans[low][high] << "\n";
}

int main() {
	int N; cin >> N; a.resize(N);
	F0R(i,N) cin >> a[i];
	dfs(0,N-1);
	cout << ans[0][N-1];
}
