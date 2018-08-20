// #include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

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

ifstream cin ("partition.in");
ofstream cout ("partition.out");

int N,K,grid[15][15],ans=225000;

bool posi(int mid, int left, int test) {
	int cur = -1, temp[15]; 
	F0R(i,15) temp[i] = 0;
	while (left >= 0 && cur < N-1) {
		cur++;
		int t = 0, flag = 0;
		F0R(i,N) {
			temp[t] += grid[cur][i];
			if (temp[t] > mid) {
				flag = 1;
				break;
			}
			if (test & (1<<i)) t ++;
		}
		if (flag) {
			cur --, left--;
			F0R(i,15) temp[i] = 0;
		}
	}
	if (left < 0) return 0;
	return 1;
}

void solve(int test) {
	int left = K;
	F0R(i,N-1) if (test & (1<<i)) left --;
	if (left<0) return;
	int lo = 0, hi = 225000;
	while (lo != hi) {
		int mid = (lo+hi)/2;
		if (posi(mid,left,test)) hi = mid;
		else lo = mid+1;
	}
	ans = min(ans,lo);
}

int main() {
	cin >> N >> K;
	F0R(i,N) F0R(j,N) cin >> grid[i][j];
	F0R(i,1<<(N-1)) solve(i);
	cout << ans;
}
