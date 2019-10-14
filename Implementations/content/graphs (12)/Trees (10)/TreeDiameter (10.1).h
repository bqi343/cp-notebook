/**
 * Description: Calculates longest path in tree
 * Source: own
 * Verification: 
   * http://www.spoj.com/problems/PT07Z/
   * https://codeforces.com/contest/1182/problem/D
 */

template<int SZ> struct TreeDiameter {
	int n; 
	vi adj[SZ];
	void addEdge(int a, int b) { adj[a].pb(b), adj[b].pb(a); }

	int par[SZ], dist[SZ];
	void dfs(int x) {
		trav(y,adj[x]) if (y != par[x]) {
			par[y] = x; dist[y] = dist[x]+1;
			dfs(y);
		}
	}
	void genDist(int x) { par[x] = -1; dist[x] = 0; dfs(x); }

	int diaLength;
	vi center, dia = {1,1}; 
	void init(int _n) {
		n = _n; 
		genDist(1); FOR(i,1,n+1) if (dist[i] > dist[dia[0]]) dia[0] = i; // find one endpoint of a diameter
		genDist(dia[0]); FOR(i,1,n+1) if (dist[i] > dist[dia[1]]) dia[1] = i;
		diaLength = dist[dia[1]];
		
		int cen = dia[1]; F0R(i,diaLength/2) cen = par[cen];
		if (diaLength&1) center = {cen,par[cen]};
		else center = {cen};
	}
};
