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
const int MX = 1e5+5;

int N,K;
vector<int> adj[MX];
bool bad = 0;
 
bool ok(const vector<int>& V, int mid) {
	int l = 0, r = (int)V.size()-1;
	for (int i = 0; i < V.size()/2; ++i) {
		if (l == mid) l ++;
		if (r == mid) r --;
		if (V[l]+V[r] < K) return 0;
		l ++, r --;
	}
	return 1;
}
 
int DFS(int x, int y) {
	if (bad) return -1;
	vector<int> v; 
	for (auto t: adj[x]) if (t != y) {
		int d = DFS(t,x)+1; if (bad) return -1;
		v.push_back(min(K,d));
	}
	sort(begin(v),end(v));
	bool al = 1;
	int mx = -MOD;
	{
		auto V = v; if (V.size()&1) V.insert(V.begin(),0);
		al = ok(V,-1);
	}
	{
		auto V = v; if (!(V.size()&1)) V.insert(V.begin(),0);
		int lo = -1, hi = V.size()-1;
		while (lo < hi) {
			int mid = (lo+hi+1)/2;
			if (ok(V,mid)) lo = mid;
			else hi = mid-1;
		}
		if (lo >= 0) mx = V[lo];
	}
	if (x == 1) {
		if (!al) bad = 1;
		return -1;
	}
	if (mx != -MOD) return mx;
	if (al) return 0;
	bad = 1; return -1;
}
 
bool SOLVE(int k) {
	K = k; bad = 0; DFS(1,0);
	return !bad;
}
 
void SOLVE() {
	int lo = 1, hi = N-1;
	while (lo < hi) {
		int mid = (lo+hi+1)/2;
		if (SOLVE(mid)) lo = mid;
		else hi = mid-1;
	}
	cout << lo << "\n";
}
 
int main() {
	// setIO(); 
	cin >> N;
	for (int i = 1; i < N; ++i) {
		int a,b; cin >> a >> b;
		adj[a].push_back(b), adj[b].push_back(a);
	}
	SOLVE();
}