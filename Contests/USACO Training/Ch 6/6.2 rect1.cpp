/*
ID: bqi3431
PROG: rect1
LANG: C++11
*/

#include <fstream>
#include<vector>
#include<iostream>
#include<algorithm>
#include<set>
#include<map>

using namespace std;
 
typedef vector<int> vi;
typedef pair<int, int> pi;

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = b-1; i >= a; i--)
#define F0Rd(i,a) for (int i = a-1; i >= 0; i--)
 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

//ifstream cin ("rect1.in");
//ofstream cout ("rect1.out");

vector<pair<pair<pi,pi>,int>> x;
int ans[2501];

void update(int llx, int urx, int lly, int ury, int c) {
	vector<pair<pair<pi,pi>,int>> k;
	k.pb({{{llx,urx},{lly,ury}},c});
	
	for (auto z: x) {
		if (urx <= z.f.f.f || llx >= z.f.f.s || ury <= z.f.s.f || lly >= z.f.s.s) {
			k.pb(z);
			continue;
		}
		if (urx < z.f.f.s) k.pb({{{urx,z.f.f.s},z.f.s},z.s});
		if (llx > z.f.f.f) k.pb({{{z.f.f.f,llx},z.f.s},z.s});
		if (ury < z.f.s.s) k.pb({{{max(llx,z.f.f.f),min(urx,z.f.f.s)},{ury,z.f.s.s}},z.s});
		if (lly > z.f.s.f) k.pb({{{max(llx,z.f.f.f),min(urx,z.f.f.s)},{z.f.s.f,lly}},z.s});
	}
	
	x = k;
}

int main() {
	int W,H,N; cin >> W >> H >> N;
	x.pb({{{0,W},{0,H}},1});
	F0R(i,N) {
		int llx, lly, urx, ury, c;
		cin >> llx >> lly >> urx >> ury >> c;
		update(llx,urx,lly,ury,c);
	}
	for (auto a: x) ans[a.s] += (a.f.f.s-a.f.f.f)*(a.f.s.s-a.f.s.f);
	FOR(i,1,2501) if (ans[i]) cout << i << " " << ans[i] << "\n";
}
