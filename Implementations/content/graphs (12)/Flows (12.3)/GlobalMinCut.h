/**
 * Description: Used only once. Stoer-Wagner, find a global minimum cut in 
 	* an undirected graph as represented by an adjacency matrix.
 * Time: O(N^3)
 * Source: Stanford Notebook, http://www.cs.tau.ac.il/~zwick/grad-algo-08/gmc.pdf
 	* https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
 	* Alternatively, use https://en.wikipedia.org/wiki/Karger%27s_algorithm
 * Verification: https://www.spoj.com/problems/ADABANKET/
 */

pair<int, vi> GlobalMinCut(vector<vi> wei) {
	int N = sz(wei);
	vi par(N); iota(all(par),0);
	pair<int,vi> bes = {INT_MAX,{}};
	R0F(phase,N) {
		vi w = wei[0]; int lst = 0;
		vector<bool> add(N,1); FOR(i,1,N) if (par[i]==i) add[i]=0;
		F0R(i,phase) {
			int k = -1; 
			FOR(j,1,N) if (!add[j] && (k==-1 || w[j]>w[k])) k = j;
			if (i+1 == phase) {
				if (w[k] < bes.f) {
					bes = {w[k],{}};
					F0R(j,N) if (par[j] == k) bes.s.pb(j);
				}
				F0R(j,N)wei[lst][j]+=wei[k][j],wei[j][lst]=wei[lst][j];
				F0R(j,N) if (par[j] == k) par[j] = lst; // merge
			} else { // greedily add closest
				F0R(j,N) w[j] += wei[k][j];
				add[lst = k] = 1;
			}
		}
	}
	return bes;
}