/**
 * Description: Used only once. Schreier-Sims lets you
	* add a permutation to a group,
	* count number of permutations in a group,
	* and test whether a permutation is a member of a group.
 * Time: ?
 * Source: MIT NULL
	* see Zlobober's post in Russian version 
	* of https://codeforces.com/blog/entry/21335
 * Verification: GP of Ekateinburg - H
 */

int n; 
vi inv(vi v) { vi V(sz(v)); F0R(i,sz(v)) V[v[i]]=i; return V; }
vi id() { vi v(n); iota(all(v),0); return v; }
vi operator*(const vi& a, const vi& b) {
	vi c(sz(a)); F0R(i,sz(a)) c[i] = a[b[i]];
	return c; }

const int N = 15;
struct Group {
	bool flag[N];
	vi sigma[N]; // sigma[t][k] = t, sigma[t][x] = x if x > k
	vector<vi> gen;
	void clear(int p) {
		memset(flag,0,sizeof flag);
		flag[p] = 1; sigma[p] = id(); gen.clear();
	}
} g[N];
bool check(const vi& cur, int k) {
	if (!k) return 1;
	int t = cur[k];
	return g[k].flag[t] ? check(inv(g[k].sigma[t])*cur,k-1) : 0;
}
void updateX(const vi& cur, int k);
void ins(const vi& cur, int k) {
	if (check(cur,k)) return;
	g[k].gen.pb(cur);
	F0R(i,n) if (g[k].flag[i]) updateX(cur*g[k].sigma[i],k);
}
void updateX(const vi& cur, int k) {
	int t = cur[k]; // if flag, fixes k -> k
	if (g[k].flag[t]) ins(inv(g[k].sigma[t])*cur,k-1); 
	else { g[k].flag[t] = 1, g[k].sigma[t] = cur;
		each(x,g[k].gen) updateX(x*cur,k); }
}
ll order(vector<vi> gen) { 
	assert(sz(gen)); n = sz(gen[0]); F0R(i,n) g[i].clear(i);
	each(a,gen) ins(a,n-1); // insert perms into group one by one
	ll tot = 1;
	F0R(i,n) {
		int cnt = 0; F0R(j,i+1) cnt += g[i].flag[j];
		tot *= cnt; }
	return tot;
}
