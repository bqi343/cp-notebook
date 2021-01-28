/**
 * Description: General matching with capacity scaling. 
 	* Assign an integer $0\le cur[i,j]\le cap[i,j]$ 
 	* to every edge such that $\sum_{j\in N(i)}cur[i,j]=f_i$,
 	* assuming that a solution exists. Correctness is questionable.
 * Time: ?
 * Source: 300iq
 * Verification: https://www.acmicpc.net/problem/18509
 */

template<int SZ> struct FakeMatch {
	int N,f[SZ],cur[SZ][SZ],cap[SZ][SZ],vis[SZ];
	void x(int a, int b, int c) {
		cur[a][b] += c, cur[b][a] += c; }
	int s,tt;
	bool dfs(int v, int sz) { // find alternating path
		vis[v] = tt;
		FOR(a,1,N+1) if (cap[v][a]-cur[v][a] >= sz) 
			if (f[a] >= 2*sz || (f[a] >= sz && a != s)) {
				x(v,a,sz); f[s] -= sz; f[a] -= sz; return 1; }
		FOR(a,1,N+1) FOR(b,1,N+1) {
			if (cap[v][a]-cur[v][a] < sz) break;
			if (cur[a][b] >= sz && vis[b] < tt) {
				x(v,a,sz); x(a,b,-sz);
				if (dfs(b,sz)) return 1;
				x(v,a,-sz); x(a,b,sz);
			}
		}
		return 0;
	}
	void solve(int _N) {
		N = _N; vpi ed; 
		FOR(i,1,N+1) FOR(j,i+1,N+1) ed.pb({i,j});
		random_shuffle(all(ed));
		each(c,ed) {
			int a = c.f, b = c.s, w = min(min(f[a],f[b]),cap[a][b]);
			x(a,b,w); f[a] -= w, f[b] -= w; }
		while (1) {
			vi lef; FOR(i,1,N+1) if (f[i]) lef.pb(i);
			if (!sz(lef)) break;
			shuffle(all(lef),rng);
			each(_s,lef) {
				s = _s; tt ++;
				for (int sz = 1<<13; sz; sz /= 2) while (f[s] >= sz) 
					{ tt ++; if (!dfs(s,sz)) break; }
			}
		}
	}
};
