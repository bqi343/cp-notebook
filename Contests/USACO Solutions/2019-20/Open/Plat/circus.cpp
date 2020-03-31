#include <bits/stdc++.h>
using namespace std;
 
void setIO(string s) {
	ios_base::sync_with_stdio(0); cin.tie(0); 
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}
 
#define f first
#define s second
 
typedef long long ll;
const int MOD = 1e9+7;
const int MX = 1e5+5;
 
struct mi {
 	int v; explicit operator int() const { return v; } 
	mi() { v = 0; }
	mi(ll _v):v(_v%MOD) { v += (v<0)*MOD; }
};
mi& operator+=(mi& a, mi b) { 
	if ((a.v += b.v) >= MOD) a.v -= MOD; 
	return a; }
mi& operator-=(mi& a, mi b) { 
	if ((a.v -= b.v) < 0) a.v += MOD; 
	return a; }
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }
mi& operator*=(mi& a, mi b) { return a = a*b; }
 
vector<int> invs, fac, ifac;
void genFac(int SZ) {
	invs.resize(SZ), fac.resize(SZ), ifac.resize(SZ); 
	invs[1] = fac[0] = ifac[0] = 1; 
	for (int i = 2; i < SZ; ++i) invs[i] = MOD-(ll)MOD/i*invs[MOD%i]%MOD;
	for (int i = 1; i < SZ; ++i) {
		fac[i] = (ll)fac[i-1]*i%MOD;
		ifac[i] = (ll)ifac[i-1]*invs[i]%MOD;
	}
}
ll comb(int a, int b) {
	if (a < b || b < 0) return 0;
	return (ll)fac[a]*ifac[b]%MOD*ifac[a-b]%MOD;
}
 
int N, par[MX];
vector<int> adj[MX];
mi ans[MX];
pair<int,int> cur[MX];
vector<pair<int,pair<int,int>>> ed;
set<int> con;
 
struct DSU {
	vector<int> e; void init(int n) { e = vector<int>(n,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
	bool unite(int len, int x, int y) { // union-by-rank
		x = get(x), y = get(y); assert(x != y);
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; 
		assert(con.count(y)); con.erase(y);
		cur[x].f += cur[y].f-2; cur[x].s += cur[y].s+len;
		return 1;
	}
};
DSU D;
 
void dfs(int x) {
	for (int t: adj[x]) if (t != par[x]) {
		par[t] = x;
		dfs(t);
	}
}
 
void dfs(int x, int lst, int d) {
	if (adj[x].size() != 2) {
		if (lst) ed.push_back({d,{x,lst}});
		d = 0; lst = x;
	}
	for (int y: adj[x]) if (y != par[x]) {
		par[y] = x;
		dfs(y,lst,d+1);
	}
}
 
int main() {
	setIO("circus");
	cin >> N; genFac(N+1);
	for (int i = 0; i < N-1; ++i) {
		int a,b; cin >> a >> b;
		adj[a].push_back(b), adj[b].push_back(a);
	}
	int root = 1; while (adj[root].size() == 2) root ++;
	dfs(root,0,0);
	sort(begin(ed),end(ed));
	for (int i = 1; i <= N; ++i) if (adj[i].size() != 2) {
		cur[i] = {adj[i].size(),0};
		con.insert(i);
	}
	ans[N] = fac[N];
	int ind = 0;
	D.init(N+1);
	for (int k = N-1; k > 0; --k) {
		while (ind < ed.size() && N-1-ed[ind].f > k) {
			D.unite(ed[ind].f,ed[ind].s.f,ed[ind].s.s);
			ind ++;
		}
		mi ret = fac[k];
		for (int t: con) ret *= ifac[(N-1-k)*(cur[t].f-1)+cur[t].s];
		ans[k] = ret;
	}
	for (int i = 1; i <= N; ++i) cout << ans[i].v << "\n";
}