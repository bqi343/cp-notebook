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

int N,sub[MX];
vector<int> adj[MX], num[MX];
bool bad = 0;
 
void dfs(int a, int b) {
	sub[a] = 1;
	for(auto& t: adj[a]) if (t != b) {
		dfs(t,a);
		sub[a] += sub[t];
		num[a].push_back(sub[t]);
	}
	if (sub[a] != N) num[a].push_back(N-sub[a]);
}
 
int cur[MX]; // basically unordered map
bool ok(int K) {
	if ((N-1)%K != 0) return 0;
	for (int i = 0; i < K; ++i) cur[i] = 0;
	for (int i = 1; i <= N; ++i) {
		int cnt = 0;
		for (auto& t: num[i]) {
			int z = t%K; if (z == 0) continue;
			if (cur[K-z]) cur[K-z] --, cnt --;
			else cur[z] ++, cnt ++;
		}
		if (cnt) return 0; // paths don't pair up
	}
	return 1;
}
 
int main() {
	setIO("deleg"); 
	cin >> N;
	for (int i = 1; i < N; ++i) {
		int a,b; cin >> a >> b;
		adj[a].push_back(b), adj[b].push_back(a);
	}
	dfs(1,0);
	for (int i = 1; i < N; ++i) {
		if (ok(i)) cout << 1;
		else cout << 0;
	}
	cout << "\n";
}