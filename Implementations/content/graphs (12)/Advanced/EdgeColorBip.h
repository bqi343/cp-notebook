=/**
 * Description: Partition each edge of bipartite graph into one of
 	* $maxDeg$ parts such that no two edges in the same part share
 	* a vertex.
 * Time: O(M\log M)
 * Source: https://www.tau.ac.il/~nogaa/PDFS/lex2.pdf
 	* maybe also check https://codeforces.com/blog/entry/75431
 * Verification: https://judge.yosupo.jp/problem/bipartite_edge_coloring
 */

template<int SZ, bool directed> struct Euler { // modified Euler cycle
	vpi adj[SZ]; vpi::iterator its[SZ];
	bool inVert[SZ]; vi verts;
	vector<bool> used;
	Euler() { F0R(i,SZ) inVert[i] = 0; }
	vi ans;
	void clr() {
		each(t,verts) adj[t].clear(), inVert[t] = 0;
		verts.clear(); used.clear(); ans.clear();
	}
	void addVert(int x) {
		if (inVert[x]) return;
		inVert[x] = 1; verts.pb(x);
	}
	void ae(int a, int b) {
		int M = sz(used); used.pb(0); 
		addVert(a); addVert(b);
		adj[a].eb(b,M); if (!directed) adj[b].eb(a,M); 
	}
	void go(int src) {
		vector<pair<pi,int>> ret, s = {{{src,-1},-1}}; 
		// {{vert, prev vert}, edge label}
		while (sz(s)) {
			int x = s.bk.f.f; auto& it = its[x], en = end(adj[x]);
			while (it != en && used[it->s]) it ++;
			if (it == en) { // no more edges out of vertex
				if (sz(ret) && ret.bk.f.s != x) exit(5);
				ret.pb(s.bk), s.pop_back(); 
			} else { s.pb({{it->f,x},it->s}); used[it->s] = 1; }
		}
		F0R(i,sz(ret)-1) ans.pb(ret[i].s);
		assert(sz(ans)%2 == 0);
	}
	array<vi,2> tour() {
		each(v,verts) {
			assert(sz(adj[v])%2 == 0);
			its[v] = begin(adj[v]);
		}
		each(v,verts) each(e,adj[v]) if (!used[e.s]) go(v);
		array<vi,2> res; F0R(i,sz(ans)) res[i%2].pb(ans[i]);
		return res;
	}
};

typedef array<int,2> T;
struct EdgeColorBip {
	int N; vector<T> ed; // # verts on each side, edges
	Euler<200000,0> E; // at least 2*N
	array<vi,2> split(vi lab) { // K is even, split into two parts
		E.clr(); each(t,lab) E.ae(ed[t][0],ed[t][1]);
		auto v = E.tour(); // get half edges on each
		F0R(i,2) each(t,v[i]) t = lab[t];
		return v;
	}
	vi match(vi lab) { // find perfect matching in MlogM
		assert(sz(lab) && sz(lab)%N == 0); int K = sz(lab)/N;
		int p = 0; while ((1<<p) < N*K) p ++; 
		int a = (1<<p)/K; int b = (1<<p)-K*a; // multiply edge good edge by a
		vi cntGood(sz(lab),a), cntBad(N,b); // now each edge is adjacent to 2^t
		for (;p;--p) { // divide by two!!
			E.clr(); vi tmp;
			F0R(i,N*K) {
				if (cntGood[i]&1) E.ae(ed[lab[i]][0],ed[lab[i]][1]), tmp.pb(i);
				cntGood[i] /= 2;
			}
			int numLab = sz(tmp);
			F0R(i,N) {
				if (cntBad[i]&1) E.ae(i,N+i), tmp.pb(i);
				cntBad[i] /= 2;
			}
			array<vi,2> x = E.tour(); T cnt = T();
			F0R(i,2) each(t,x[i]) cnt[i] += t >= numLab;
			if (cnt[0] > cnt[1]) swap(x[0],x[1]);
			each(t,x[0]) {
				if (t < numLab) cntGood[tmp[t]] ++;
				else cntBad[tmp[t]] ++;
			}
		}
		vi v; F0R(i,sz(lab)) if (cntGood[i]) v.pb(lab[i]);
		assert(sz(v) == N);
		return v;
	}
	vector<bool> used;
	vector<vi> edgeColor(vi lab) { // regular bipartite graph!
		assert(sz(lab)%N == 0); int K = sz(lab)/N;
		if (K == 0) return {};
		if (K == 1) return {lab};
		if (pct(K) == 1) {
			array<vi,2> p = split(lab); 
			vector<vi> a = edgeColor(p[0]), b = edgeColor(p[1]);
			a.insert(end(a),all(b)); return a;
		}
		if (K%2 == 0) {
			array<vi,2> p = split(lab); auto a = edgeColor(p[0]);
			int cur = K/2;
			while (pct(cur)>1) {
				cur ++; p[1].insert(end(p[1]),all(a.bk));
				a.pop_back();
			}
			auto b = edgeColor(p[1]); a.insert(end(a),all(b)); return a;
		} else {
			vi v = match(lab); each(t,v) used[t] = 1;
			vi LAB; each(t,lab) if (!used[t]) LAB.pb(t);
			each(t,v) used[t] = 0;
			auto a = edgeColor(LAB); a.pb(v); return a;
		}
	}
	vector<vi> calc(vector<T> _ed) {
		T side = T(); each(t,_ed) F0R(i,2) ckmax(side[i],t[i]+1);
		vi deg[2], cmp[2], sz[2]; 
		F0R(i,2) deg[i].rsz(side[i]), cmp[i].rsz(side[i]);
		each(t,_ed) F0R(i,2) deg[i][t[i]] ++;
		int K = 0; F0R(i,2) each(t,deg[i]) ckmax(K,t);
		F0R(s,2) for (int i = 0; i < side[s]; ) {
			sz[s].pb(0);
			while (i < side[s] && sz[s].bk+deg[s][i] <= K) 
				cmp[s][i] = sz(sz[s])-1, sz[s].bk += deg[s][i++]; 
		}
		F0R(i,2) while (sz(sz[i]) < sz(sz[i^1])) sz[i].pb(0);
		N = sz(sz[0]); 
		each(t,_ed) ed.pb({cmp[0][t[0]],N+cmp[1][t[1]]});
		int ind = 0;
		F0R(i,N) while (sz[0][i] < K) {
			while (sz[1][ind] == K) ind ++;
			sz[0][i] ++, sz[1][ind] ++; ed.pb({i,N+ind});
		}
		used.rsz(N*K); vi lab(N*K); iota(all(lab),0);
		return edgeColor(lab);
	}
};
