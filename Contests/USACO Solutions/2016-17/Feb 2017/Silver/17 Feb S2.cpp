#include<iostream>
#include<fstream>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)

int bad[100001];

int main() {
	//ifstream cin ("maxcross.in");
	//ofstream cout ("maxcross.out");
	int N,K,B; cin >> N >> K >> B;
	F0R(i,B) {
		int b; cin >> b;
		bad[b] = 1;
	}
	int low = 1, high = K, cur = 0, ans = 1000000007;
	FOR(i,low,high+1) cur += bad[i];
	while (1) {
		ans = min(ans,cur);
		if (high == N) break;
		cur += (bad[++high] - bad[low++]);
	}
	cout << ans;
}