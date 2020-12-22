#include <bits/stdc++.h>
using namespace std;
 
using pi = pair<int,int>;
#define f first
#define s second
#define sz(x) int((x).size())
 
int N,ans,eq;
vector<pi> cows;
 
void solve() {
	sort(begin(cows),end(cows));
	for (int a = 0; a < N; ++a) { // leftmost cow i
		set<int> sorted_y;
		for (int b = a+1; b < N; ++b) { // rightmost cow j
			if (a < b-1) sorted_y.insert(cows[b-1].s);
			int len = cows[b].f-cows[a].f; // side length of square
			int lo = max(cows[a].s,cows[b].s)-len, hi = min(cows[a].s,cows[b].s); 
			if (lo > hi) continue;
 
			// initialize the square as [cows[a].f,cows[b].f] x [lo,lo+len]
			vector<int> y(begin(sorted_y),end(sorted_y)); 
			int l = 0, r = -1;
			// find cow of lowest y-coordinate that square currently contains
			while (l < sz(y) && lo >= y[l]+1) l ++; 
			// find cow of highest y-coordinate that square currently contains
			while (r+1 < sz(y) && lo >= y[r+1]-len) r ++; 
			// initial square currently includes cows [l,r]
 
			while (1) { // repeatedly increase y
				++ ans;
				int yl = min(cows[a].s,cows[b].s), yr = max(cows[a].s,cows[b].s);
				if (l <= r) yl = min(yl,y[l]), yr = max(yr,y[r]);
				assert(yr-yl <= len); 
				eq += yr-yl == len; // width is equal to height
				// current bounding rectangle is [cows[a].f,cows[b].f] x [yl,yr]
				int leave_bottom = (l < sz(y) ? y[l]+1 : INT_MAX); 
				int enter_top    = (r+1 < sz(y) ? y[r+1]-len : INT_MAX);
				int change_y = min(leave_bottom ,enter_top); // find min y such that set changes
				if (change_y > hi) break;
				l += leave_bottom == change_y;
				r += enter_top == change_y;
			}
		}
	}
}
 
int main() {
	cin >> N;
	cows.resize(N); 
	for (pi& cow: cows) cin >> cow.f >> cow.s;
	ans = N+1;
	solve();
	for(pi& cow: cows) swap(cow.f,cow.s);
	solve();
	assert(eq%2 == 0); // bounding rectangles with equal width as height counted twice
	cout << ans-eq/2;
}
 
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/
 