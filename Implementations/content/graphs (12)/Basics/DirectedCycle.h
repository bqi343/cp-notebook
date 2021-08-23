/**
 * Description: skack
 * Source: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 * Verification: VT HSPC 2019 D
 */

template<int SZ> struct DirCyc {
	vi adj[SZ], stk, cyc; V<bool> inStk, vis; 
	void dfs(int x) {
		stk.pb(x); inStk[x] = vis[x] = 1;
		each(i,adj[x]) {
			if (inStk[i]) cyc = {find(all(stk),i),end(stk)};
			else if (!vis[i]) dfs(i); 
			if (sz(cyc)) return;
		}
		stk.pop_back(); inStk[x] = 0;
	}
	vi init(int N) {
		inStk.rsz(N), vis.rsz(N); 
		F0R(i,N) if (!vis[i] && !sz(cyc)) dfs(i);
		return cyc;
	}
};
