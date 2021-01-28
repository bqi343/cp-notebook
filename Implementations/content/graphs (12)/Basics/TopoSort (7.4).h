/**
 * Description: sorts vertices such that if there exists an edge x->y, then x goes before y
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/quantumsuperposition
 */

struct TopoSort {
	int N; vi in, res;
	V<vi> adj;
	void init(int _N) { N = _N; in.rsz(N); adj.rsz(N); }
	void ae(int x, int y) { adj[x].pb(y), in[y] ++; }
	bool sort() {
		queue<int> todo; 
		F0R(i,N) if (!in[i]) todo.push(i);
		while (sz(todo)) {
			int x = todo.ft; todo.pop(); res.pb(x);
			each(i,adj[x]) if (!(--in[i])) todo.push(i);
		}
		return sz(res) == N;
	}
};
