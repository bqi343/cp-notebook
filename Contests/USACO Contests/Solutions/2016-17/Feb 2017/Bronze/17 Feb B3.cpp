#include <bits/stdc++.h>

using namespace std;
 
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define f first
#define s second

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);
	int n, ans = 0; cin >> n;
	vector<pi> cow(n);
	F0R(i,n) cin >> cow[i].f >> cow[i].s;
	sort(cow.begin(),cow.end());
	F0R(i,n) {
		int cur = cow[i].f;
		FOR(j,i,n) cur += cow[j].s;
		ans = max(ans,cur);
	}
	cout << ans;
}
