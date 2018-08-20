#include <bits/stdc++.h>

/*#include <fstream>
#include <algorithm>*/

using namespace std;
 
#define ll long long
#define mp make_pair
#define pb push_back
#define pi pair <int, int>
#define vi vector<int>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define FORd(i, a, b) for (int i=a-1; i>=b; i--)
#define F0Rd(i, a) for (int i=a-1; i>=0; i--)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second
#define be begin
#define e end
#define lb lower_bound
#define ub upper_bound
 
const int MOD = 1000000007;

ll A,B,n,m,a1=0,b1=0,curv=0, curh=0;
ll ans = 0;
vector<ll> v1, h1, vert, hor;

int main() {
	// freopen("fencedin.in", "r", stdin);
  	// freopen("fencedin.out", "w", stdout);
	scanf("%d%d%d%d",&A,&B,&n,&m);
	v1.pb(0), v1.pb(A), h1.pb(0), h1.pb(B);
	
	F0R(i,n) scanf("%d",&a1), v1.pb(a1);
	F0R(i,m) scanf("%d",&b1), h1.pb(b1);
	
	sort(h1.begin(),h1.end()), sort(v1.begin(),v1.end());
	F0R(i,m+1) hor.pb(h1[i+1]-h1[i]);
	F0R(i,n+1) vert.pb(v1[i+1]-v1[i]);
	sort(vert.begin(),vert.end()), sort(hor.begin(),hor.end());
	
	ans += 1ll*m*vert[0]+1ll*n*hor[0];
	// cout << ans << endl;
	curh++,curv++;
	vert.erase(vert.begin()), hor.erase(hor.begin());
	
	while (curh <= m && curv <= n) {
		if (hor[0]<vert[0]) {
			curh++;
			ans += 1ll*hor[0]*(n+1-curv);
			hor.erase(hor.begin());
		} else {
			curv++;
			ans += 1ll*vert[0]*(m+1-curh);
			vert.erase(vert.begin());
		}
		// cout << ans << endl;
	}
	printf("%lld",ans);
	return 0;
}
