/**
 * Description: Biconnected components, removing any vertex in component 
 	* doesn't disconnect it. To get block-cut tree, create a bipartite graph
 	* with the original vertices on the left and a vertex for each BCC on the right. 
 	* Draw edge $u\leftrightarrow v$ if $u$ is contained within the BCC for $v.$
 * Time: O(N+M)
 * Source: GeeksForGeeks (corrected)
 * Verification: 
 	* USACO December 2017, Push a Box -> https://pastebin.com/yUWuzTH8
 	* https://cses.fi/problemset/task/1705/
 */

template<int SZ> struct BCC {
	vpi adj[SZ], ed;
	void ae(int u, int v) { 
		adj[u].eb(v,sz(ed)), adj[v].eb(u,sz(ed)), ed.eb(u,v); }
	int N, disc[SZ];
	vi st; vector<vi> bccs; // edges for each bcc
	int bcc(int u, int p = -1) { // return lowest disc
		static int ti = 0; int low = disc[u] = ++ti, child = 0;
		trav(i,adj[u]) if (i.s != p) {
			if (!disc[i.f]) {
				child ++; st.pb(i.s);
				int LOW = bcc(i.f,i.s); ckmin(low,LOW);
				// if (disc[u] < LOW) -> bridge
				if (disc[u] <= LOW) { // get edges in bcc
					// if (p != -1 || child > 1) -> u is articulation pt
					bccs.eb(); vi& tmp = bccs.bk; // new bcc
					for (bool done = 0; !done; tmp.pb(st.bk),
						st.pop_back()) done |= st.bk == i.s;
				}
			} else if (disc[i.f] < disc[u]) 
				ckmin(low,disc[i.f]), st.pb(i.s);
		}
		return low;
	}
	void init(int _N) {
		N = _N; F0R(i,N) disc[i] = 0;
		F0R(i,N) if (!disc[i]) bcc(i); 
		/// st should be empty after each iteration
	}
};