#include "bits/stdc++.h"
using namespace std;

void setIO(string s) {
	ios_base::sync_with_stdio(0); cin.tie(0); 
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
 
int N;
bool G[300][300],GG[300][300];
long long ans;
 
void rot() {
	for (int i = 0; i < N; ++i) 
		for (int j = 0; j < N; ++j) 
			GG[N-1-j][i] = G[i][j];
	for (int i = 0; i < N; ++i) 
		for (int j = 0; j < N; ++j) 
			G[i][j] = GG[i][j];
}
void solve() { // corner in diagonal with sum a, other two vertices in diagonal with sum b
	for (int a = 0; a < 2*N-1; ++a) 
		for (int b = a+2; b < 2*N-1; b += 2) {
			int dif = (b-a)/2, st = max(0,a-(N-1)), en = min(a,N-1);
			int cur = 0;
			for (int i = st; i <= en; ++i) { 
				if (i == st) // consider (i,a-i) -> stuff in row b
					for (int j = max(i,b-(N-1)); j < min(i+dif,N-dif); ++j) 
						cur += G[j][b-j] && G[j+dif][b-j-dif];
				if (G[i][a-i]) ans += cur;
				if (i+2*dif < N && b-(i+dif) < N) 
					cur += G[i+dif][b-i-dif] && G[i+2*dif][b-i-2*dif];
				if (i+dif < N && b-i < N) 
					cur -= G[i][b-i] && G[i+dif][b-i-dif];
			}
		}
}
int main() {
	setIO("triangles"); 
	cin >> N;
	for (int i = 0; i < N; ++i) 
		for (int j = 0; j < N; ++j) {
			char c; cin >> c;
			G[i][j] = c == '*';
		}
	for (int i = 0; i < 4; ++i) solve(), rot(); 
	cout << ans << "\n";
}