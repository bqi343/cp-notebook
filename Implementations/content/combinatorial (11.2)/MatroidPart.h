/**
 * Description: Find three edge-disjoint spanning trees 
 	* (matroid partition)
 * Time: ?
 * Source: https://codeforces.com/blog/entry/69287
 	* chilli (KACTL)
 * Verification: https://dmoj.ca/problem/dmopc19c3p6
 * Usage: MatroidPart<Gmat>(n,3,3*(N-1),Gmat(ed))
 */

 struct Gmat { // graphic matroid
	int V = 0; vpi ed; DSU D;
	vi depth;
	vector<vpi> adj;
	vpi pre;
	Gmat(vpi ed):ed(ed) {
		map<int,int> m; each(t,ed) m[t.f] = m[t.s] = 0;
		each(t,m) t.s = V++; 
		each(t,this->ed) t.f = m[t.f], t.s = m[t.s];
	}
	void clear() { D.init(V); adj = vector<vpi>(V); }
	void ins(int i) { assert(D.unite(ed[i].f,ed[i].s)); 
		adj[ed[i].f].pb({ed[i].s,i});
		adj[ed[i].s].pb({ed[i].f,i});
	}
	bool indep(int i) { return !D.sameSet(ed[i].f,ed[i].s); }
	vi backEdges(int x) {
		int a = ed[x].f, b = ed[x].s;
		vi v;
		while (a != b) {
			if (depth[a] < depth[b]) swap(a,b);
			v.pb(pre[a].s); a = pre[a].f;
		}
		dbg(x,a,b,v);
		return v;
	}
	void dfs(int x) {
		each(t,adj[x]) if (depth[t.f] == -1) {
			depth[t.f] = depth[x]+1;
			pre[t.f] = {x,t.s};
			dfs(t.f);
		}
	}
	void genBack() {
		depth = vi(V,-1); pre = vpi(V,{-1,-1});
		F0R(i,V) if (depth[i] == -1) {
			depth[i] = 0;
			dfs(i);
		}
	}
};

template<class M> struct MatroidPart {
	int n,k; vi iset; 
	vector<M> m;
	bool augment(int st) {
		F0R(i,k) m[i].clear();
		F0R(i,n) if (iset[i] != -1) m[iset[i]].ins(i);
		F0R(i,k) m[i].genBack();
		vi pre(n,-1); pre[st] = n; queue<int> q({st});
		while (sz(q)) {
			int x = q.ft; q.pop();
			F0R(z,k) if (z != iset[x]) {
				if (m[z].indep(x)) {
					for (; x != n; x = pre[x]) swap(z,iset[x]);
					return 1;
				}
				vi v = m[z].backEdges(x);
				each(t,v) if (pre[t] == -1) pre[t] = x, q.push(t);
			}
		}
		return 0;
	}
	MatroidPart(int n, int k, int des, M _m):n(n),k(k) {
		iset.assign(n,-1); 
		m.assign(k,_m); F0R(i,k) m[i].clear();
		int cur = 0;
		F0R(j,k) F0R(i,n) if (iset[i] == -1 && m[j].indep(i)) 
			iset[i] = j, m[j].ins(i), cur ++;
		int lef = n-cur;
		F0R(i,n) if (iset[i] == -1) {
			cur += augment(i); lef --;
			if (cur == des || cur+lef < des) break;
		}
	}
};
