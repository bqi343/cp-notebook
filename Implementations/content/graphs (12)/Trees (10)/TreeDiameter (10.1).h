/**
 * Description: Calculates longest path in tree. The vertex furthest
 	* from 0 must be an endpoint of the diameter.
 * Source: own
 * Verification: 
   * http://www.spoj.com/problems/PT07Z/
   * https://codeforces.com/contest/1182/problem/D
 */

template<int SZ> struct TreeDiameter {
	int N, par[SZ], dist[SZ], diaLen;  
	vi adj[SZ], dia, center;
	void ae(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
	void dfs(int x) {
		each(y,adj[x]) if (y != par[x]) {
			par[y] = x; dist[y] = dist[x]+1; 
			dfs(y); }
	}
	void genDist(int x) { par[x] = -1; dist[x] = 0; dfs(x); }
	void init(int _N) {
		N = _N; dia = {0,0}; 
		genDist(0); F0R(i,N) if (dist[i]>dist[dia[0]]) dia[0] = i; 
		genDist(dia[0]); F0R(i,N) if (dist[i]>dist[dia[1]]) dia[1] = i;
		diaLen = dist[dia[1]];
		int cen = dia[1]; F0R(i,diaLen/2) cen = par[cen];
		center = {cen}; if (diaLen&1) center.pb(par[cen]);
	}
};
