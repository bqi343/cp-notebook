/*
ID: bqi3431
PROG: fence8
LANG: C++11
*/

//#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

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

ifstream cin ("fence8.in");
ofstream cout ("fence8.out");

vi b,r;
int N,R,csum,sum,op,mn = 1000000007;

bool dfs(int cur, int waste) {
	if (waste+csum>sum) return 0;
	if (cur == -1) return 1;
	bool z = 0, ans = 0;
	F0R(i,N) 
		if (b[i] == r[cur]) {
			b[i] = 0;
			if (dfs(cur-1,waste)) ans = 1;
			b[i] = r[cur];
			z = 1;
			break;
		}
	if (!z) F0R(i,N) if (r[cur] <= b[i]) {
		b[i] -= r[cur];
		int w1 = waste;
		if (b[i]<mn) w1 += b[i];
		if (dfs(cur-1,w1)) ans = 1;
		b[i] += r[cur];
		if (ans == 1) break;
	}
	return ans;
}

void input() {
	cin >> N; b.resize(N);
	F0R(i,N) {
		cin >> b[i];
		sum += b[i];
	}
	cin >> R;  r.resize(R);
	F0R(i,R) {
		cin >> r[i];
		mn = min(mn,r[i]);
	}
	sort(r.begin(),r.end());
}

int main() {
	input();
	F0R(i,R) {
		csum += r[i];
		if (csum > sum || !dfs(i,0)) {
			cout << i << "\n";
			return 0;
		}
	}
	cout << R << "\n";
}
