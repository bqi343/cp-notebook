#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)

int main() {
	//ifstream cin ("crossroad.in");
	//ifstream cout ("crossroad.out");
	
	int cur[11];
	F0R(i,11) cur[i] = -1;
	int n, ans = 0;  cin >> n;
	F0R(i,n) {
		int a,b; cin >> a >> b;
		if (cur[a] != -1 && cur[a] != b) ans++;
		cur[a] = b;
	}
	cout << ans;
}