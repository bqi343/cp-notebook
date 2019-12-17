#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef vector<int> vi; 
 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)
 
#define pb push_back
#define rsz resize
#define sz(x) int(x.size())
 
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; }
	
void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}
 
const int MX = 300;
 
int N,M,dp[MX][MX];
int mx[MX][MX][MX];
vi w,l,r;
 
int main() {
	setIO("pieaters"); 
	cin >> N >> M;
	w.rsz(M); l.rsz(M), r.rsz(M);
	F0R(i,M) {
		cin >> w[i] >> l[i] >> r[i]; 
		l[i] --,r[i] --;
		FOR(j,l[i],r[i]+1) 
			ckmax(mx[j][l[i]][r[i]],w[i]);
	}
	F0R(i,N) {
		R0F(j,i+1) FOR(k,i,N) {
			if (j) ckmax(mx[i][j-1][k],mx[i][j][k]);
			if (k < N-1) ckmax(mx[i][j][k+1],mx[i][j][k]);
		}
	}
	R0F(a,N) FOR(b,a,N) {
		FOR(c,a,b) ckmax(dp[a][b],dp[a][c]+dp[c+1][b]);
		FOR(c,a,b+1) if (mx[c][a][b]) { // among all those covering c >= a
			int res = mx[c][a][b];
			if (c > a) res += dp[a][c-1];
			if (c < b) res += dp[c+1][b];
			ckmax(dp[a][b],res);
		}
	}
	cout << dp[0][N-1] << "\n";
}