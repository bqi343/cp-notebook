/**
 * Description: use stack
 * Source: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 * Verification: VT HSPC 2019 D
 */

template<int SZ> struct DirCyc {
	vi adj[SZ], st;
	bool inSt[SZ], vis[SZ];
	vi dfs(int x) {
		st.pb(x); inSt[x] = vis[x] = 1;
		trav(i,adj[x]) {
			if (inSt[i]) {
				int ind = sz(st)-1; while (st[ind] != i) ind --;
				return vi(begin(st)+ind,end(st));
			} else if (!vis[i]) {
				vi v = dfs(i); if (sz(v)) return v;
			}
		}
		st.pop_back(); inSt[x] = 0;
	}
	vi init(int n) {
		st.clear(); F0R(i,n) inSt[i] = vis[i] = 0;
		F0R(i,n) if (!vis[i]) {
			vi v = dfs(i);
			if (sz(v)) return v;
		}
		return {};
	}
};