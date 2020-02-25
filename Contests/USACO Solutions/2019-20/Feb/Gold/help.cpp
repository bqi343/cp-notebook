#include "bits/stdc++.h"
 
using namespace std;
 
void setIO(string s) {
	ios_base::sync_with_stdio(0); cin.tie(0); 
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
 
#define f first
#define s second
 
const int MOD = 1e9+7;
 
int N;
 
int main() {
	setIO("help");
	cin >> N; vector<pair<int,int>> v(N);
	for (auto& a: v) cin >> a.f >> a.s;
	vector<int> over(2*N+1), po2(N);
	po2[0] = 1; for (int i = 1; i < N; ++i) po2[i] = 2*po2[i-1]%MOD;
	for (auto& t: v) over[t.f] ++, over[t.s] --; 
	for (int i = 1; i <= 2*N; ++i) over[i] += over[i-1];
	int ans = 0; for (auto& t: v) ans = (ans+po2[N-1-over[t.f-1]])%MOD;
	cout << ans << "\n";
}