/**
 * Description: stack
 * Source: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 * Verification: VT HSPC 2019 D
 */

template<int SZ> struct DirCyc {
	vi adj[SZ], st, cyc; vector<bool> inSt, vis; 
	void dfs(int x) {
		st.pb(x); inSt[x] = vis[x] = 1;
		each(i,adj[x]) {
			if (inSt[i]) cyc = {find(all(st),i),end(st)};
			else if (!vis[i]) dfs(i); 
			if (sz(cyc)) return;
		}
		st.pop_back(); inSt[x] = 0;
	}
	vi init(int N) {
		inSt.rsz(N), vis.rsz(N); 
		F0R(i,N) if (!vis[i] && !sz(cyc)) dfs(i);
		return cyc;
	}
};
